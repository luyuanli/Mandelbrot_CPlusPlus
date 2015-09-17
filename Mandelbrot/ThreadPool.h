//ThreadPool.h

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool{
private:
	vector<thread>          threads;
	queue< function<void()> > jobQueue;
	mutex                   mtx;
	condition_variable      cv;
	bool                    quit;
	bool                    stopped;
	void                    Run();  
public:
	ThreadPool(int numberOfThreads);
	~ThreadPool();
	void addJob(function<void()> job);
	void ShutDown();
};
