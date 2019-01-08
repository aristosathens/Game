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
#include <thread>
#include <vector>

//
// Class
//

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
    void schedule(const std::function<void(void)>& thunk);
    void wait();

    //
    // Private
    //
    private:
    std::thread dispatcher;
    std::vector<std::thread> workers;
};

#endif // THREAD_POOL_H