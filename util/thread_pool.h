// Aristos Athens

//
// Compiler guard
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

//
// Include
//

#include <functional>
#include <mutex>
#include <queue>
#include <semaphore.h>
#include <thread>
#include <vector>

//
// Types
//

using thunk_t = std::function<void(void)>;

//
// Classes
//

// Maintains info about the state of a worker thread.
struct worker_t
{
    worker_t() : available(true) {}

    size_t ID_number;
    bool available;
    std::semaphore worker_semaphore;
    thunk_t function;
}

// Maintains a dispatcher thread and a collection of worker threads.
class ThreadPool
{
    // Remove copy constructor and assignment operator.
    ThreadPool(const ThreadPool& original) = delete;
    ThreadPool& operator=(const ThreadPool& rhs) = delete;

    //
    // Public
    //
    public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    void schedule(const thunk_t& thunk);
    void wait();

    //
    // Private
    //
    private:
    void dispatcher_func();
    void worker_func(size_t);
    size_t get_available_worker_index();

    // Main thread for sending requests to worker threads.
    std::thread dispatcher;

    // Use in dispatcher to check if any workers are available.
    semaphore workers_semaphore;

    // Worker info structs, worker threads, and worker access mutexes.
    std::vector<worker_t> workers;
    std::vector<std::thread> worker_threads;
    std::vector<std::mutex> worker_mutexes;

    // Use in dispatcher to check if any new functions are available.
    semaphore functions_semaphore;

    // Functions queue and queue access mutex.
    std::mutex functions_mutex;
    std::queue<std::functions<void(void)>> functions;

    // Structures for maintaining function counts.
    std::conditional_variable_any cv;
    std::mutex cv_mutex;
    size_t num_functions_left;

    // Structures for signaling object's end of life.
    std::muex ending_mutex;
    bool ending;
};

#endif // THREAD_POOL_H