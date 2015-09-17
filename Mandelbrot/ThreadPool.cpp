#include "ThreadPool.h"

ThreadPool::ThreadPool(int numberOfThreads)
	: quit(false), stopped(false)
{
	for (int t = 0; t < numberOfThreads; t++)
		threads.push_back(std::thread(&ThreadPool::Run, this));

	// NOTE: The above line is tricky: 
	// how to add a function pointer to a member function of a class
	// to a STL container, so I am giving you the exact line of code

	// Notice it needs to know about the member function as well as 'this' 
	// which is the pointer to class data.
}

ThreadPool::~ThreadPool()
{
	//if not stopped, call ShutDown
	if (!stopped)
		ShutDown();
}

void ThreadPool::ShutDown()
{
	{
    //	lock the thread pool
	std::unique_lock<std::mutex> lock(mtx);
	//	set the 'quit' flag
	quit = true;
    }

	//wake up all threads
	cv.notify_all();

	//	join all threads  // wait for threads to exit
	for (size_t i = 0; i < threads.size(); i++)
		threads[i].join();

	//	set the stopped flag
	stopped = true;
}

void ThreadPool::addJob(function<void()> job)
{
	//if 'stopped', throw “thread pool shutdown, not accepting jobs”
	//if 'quit', throw “thread pool shutting down, not accepting jobs”

	{
	//lock the thread pool
		std::unique_lock<std::mutex> lock(mtx);
	//push 'job' onto the 'jobQueue'
		jobQueue.push(job);
	}
	
	//wake up one thread
	cv.notify_one();
}

void ThreadPool::Run() // note this is a private member function
{
	std::function<void()> job;

	while (true)
	{
		{
			//lock the thread pool
			std::unique_lock<std::mutex> lock(mtx);

			/*wait on the condition variable for a job to arrive
				to prevent sperious wakeups, code a lambda
				function which returns true if either
				- jobs are available(use job.empty())
				- or the quit flag is set*/
			cv.wait(lock, [this]{return quit || !jobQueue.empty(); });

			//if the quit flag is set and there aren't any jobs, return
			if (quit && jobQueue.empty())
				return;

			//get the job off the job queue
			job = jobQueue.front();
			jobQueue.pop();

		}

		job();
	}

}
