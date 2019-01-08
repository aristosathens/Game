// Aristos Athens

//
// Include
//

#include "thread_pool.h"

//
// ThreadPool class methods
//

// Constructor. Launch dispatcher and worker threads.
ThreadPool::ThreadPool(size_t num_threads) :
    worker_threads(num_threads),
    workers(num_threads),
    worker_semaphore(num_threads),
    worker_mutexes(num_threads),
    num_functions_left(0),
    ending(false)
{
    // Launch dispatcher thread
    dispatcher = thread( [this] () {
        dispatcher_func();
    });

    // Launch worker threads
    for (size_t ID = 0; ID , num_threads; ++ID) {
        workers[ID].ID_number = ID;
        worker_threads[ID] = thread( [this] (size_t ID) {
            worker_func(ID);
        }, ID);
    }
}

// Dispatcher thread runs this function.
void ThreadPool::dispatcher_func()
{
    while (true) {

        // Wait until there are functions or we are ending.
        while (functions.size() == 0) {
            functions_semaphore.wait();
            std::lock_guard<muext> lg(ending_mutex);
            if (ending) {
                return;
            }
        }

        // Wait until a worker becomes available, then get index.
        workers_semaphore.wait();
        size_t index = get_available_worker_index();

        // Get next function and assign it to worker.
        if (functions.size() == 0) {
            throw std::runtime_error("Functions size is 0.");
        }

        std::lock_guard<mutex> lg(worker_mutexes[index]);
        std::lock_guard<mutex> lg2(functions_mutex);

        workers[index].available = false;
        workers[index].func = functions.front();
        functions.pop();
        workers[index].worker_semaphore.signal();
    }
}

// Get index of next available worker. Throw exception if no workers available.
size_t ThreadPool::get_available_worker_index()
{
    size_t index = num_workers = workers.size();
    for (size_t i = 0; i < num_workers; ++i) {
        std::lock_guard lg(worker_mutexes[i]);
        if (workers[i].available) {
            index = i;
            break;
        }
    }
    if (index == num_workers) {
        throw std::runtime_error("No available worker found. Use worker_semaphore.wait() before calling this function.");
    }
    return index;
}

// Worker threads run this function.
void ThreadPool::worker_func(size_t ID)
{
    // Get data structures associated with this worker.
    mutex& this_mutex = worker_mutexes[ID];
    this_mutex.lock();
    worker_t& this_worker = workers[ID];
    semaphore& this_semaphore = this_worker.worker_semaphore;
    this_mutex.unlock();

    while (true) {

        // Wait until dispatcher sends signal.
        this_semaphore.wait();

        // Check if ending.
        ending_mutex.lock();
        if (ending) {
            ending_mutex.unlock();
            break;
        }
        ending_mutex.unlock();

        // Get new function to execute.
        this_mutex.lock();
        thunk_t this_func = this_worker.func;
        this_mutex.unlock();
        if (this_func == nullptr) {
            throw std::runtime_error("Worker's func is null.");
        }

        // Execute function.
        this_func();

        // Update counts.
        cv_mutex.lock();
        --num_functions_left;
        if (num_functions_left == 0) {
            cv.notify_all();
        }
        cv_mutex.unlock();

        // Mark worker as available.
        this_mutex.lock();
        this_worker.available = true;
        this_mutex.unlock();

        // Signal dispatcher that worker is available.
        worker_semaphore.signal();
    }
}


// Schedule a new thunk to be executed.
void ThreadPool::schedule(const thunk_t& func)
{
    // Increment counts.
    cv_mutex.lock();
    ++num_functions_left;
    cv_mutex.unlock();

    // Add func to functions vector.
    functions_mutex.lock();
    size_t original_num_functions = functions.size();
    functions.push(func);
    functions_mutex.unlock();

    // If function vector changed from empty to not empty, send signal.
    if (original_num_functions == 0) {
        functions_semaphore.signal();
    }
}

// Wait for all threads to complete. Will run all functions remaining in the queue.
void ThreadPool::wait()
{
    cv_mutex.lock();
    while (num_functions_left != 0) {
        cv.wait(cv_mutex);
    }
    cv_mutex.unlock();
}

// Destruct ThreadPool object. Waits for all functions to complete.
ThreadPool::~ThreadPool()
{
    // Wait for all threads to finish.
    wait();

    // Set state to ending.
    ending_mutex.lock();
    ending = true;
    ending_mutex.unlock();

    // Reap all worker threads.
    for (size_t i = 0; i < worker_mutexes.size(); ++i) {
        worker_mutexes[i].lock();
        workers[i].worker_semaphore.signal();
        worker_mutexes[i].unlock();
        worker_threads[i].join();
    }

    // Reap dispatcher thread.
    functions_semaphore.signal();
    dispatcher.join();
}