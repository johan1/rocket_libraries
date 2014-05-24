#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <deque>
#include <functional>
#include <vector>

#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

#include <stdint.h>

#ifdef THREAD_POOL_DEBUG
	#include "../util/Log.h"
#endif

namespace rocket {

// TODO: Can we reduce the need to call a copy constructor twice? see test/tryFunctors
class ThreadPool {
public:
    ThreadPool(int numberOfWorkers);
    ~ThreadPool();

	template <typename Function, typename ...Args>
	boost::unique_future<typename std::result_of<Function(Args...)>::type>
	submit(Function &&f, Args&&... args);

private:
    class Task {
    public:
        virtual void operator()() = 0;
        virtual ~Task() {}
    };

    template <typename T>
    class SubmitTask;

	boost::atomic<bool> isShuttingDown;
    boost::thread::id const mainThreadId;

    std::vector<boost::thread> workerThreads;
    std::deque<std::unique_ptr<Task>> taskQueue;

    boost::mutex taskQueueMutex;
	boost::condition_variable waitOnQueueEmptyCondition;

    void join();
};

template <typename Function, typename ...Args>
boost::unique_future<typename std::result_of<Function(Args...)>::type>
ThreadPool::submit(Function &&f, Args&&... args) {
	std::function<typename std::result_of<Function(Args...)>::type(void)> submitFunction =
			std::bind(f, args...);
	SubmitTask<typename std::result_of<Function(Args...)>::type> *st =
			new SubmitTask<typename std::result_of<Function(Args...)>::type>(std::move(submitFunction));
	auto future = st->getFuture();
	{
		boost::lock_guard<boost::mutex> lock(taskQueueMutex);
		taskQueue.push_back(std::unique_ptr<Task>(st));
	}

	// Notify threads that queue has a new entry.
	// One thread notification is sufficient. This way we will not have more threads
	// running the necessary.
	waitOnQueueEmptyCondition.notify_one();

    return future;
}

template <typename T>
class ThreadPool::SubmitTask : public Task {
public:
    SubmitTask(std::function<T()> &&fun) : fun(fun), p() {}

    virtual void operator()() {
#ifdef THREAD_POOL_DEBUG
		LOGD("Setting task promise " << this);
#endif
		p.set_value(fun());
    }

    boost::unique_future<T> getFuture() {
		return p.get_future();
    }

	virtual ~SubmitTask() {}

private:
    std::function<T()> fun;
    boost::promise<T> p;
};

template <>
class ThreadPool::SubmitTask<void> : public Task {
public:
    SubmitTask(std::function<void()> fun) : fun(fun), p() {}

	virtual void operator()() {
		fun();
		p.set_value();
#ifdef THREAD_POOL_DEBUG
		LOGD("Setting task promise " << this);
#endif
	}

    boost::unique_future<void> getFuture() {
        return p.get_future();
    }

	virtual ~SubmitTask() {}

private:
    std::function<void()> fun;
    boost::promise<void> p;
};

}

#endif
