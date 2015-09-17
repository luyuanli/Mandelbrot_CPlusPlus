//Term Project
//Timer.h

#include <chrono>

class Timer { // C++11 chrono needs "#include <chrono>".
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop;
public:
	void Start() { start = std::chrono::high_resolution_clock::now(); }
	void Stop()  { stop = std::chrono::high_resolution_clock::now(); }
	uint64_t nsecs() {
		typedef std::chrono::duration<int, std::nano> nanosecs_t;
		nanosecs_t duration_get
			(std::chrono::duration_cast<nanosecs_t> (stop - start));
		uint64_t ns = duration_get.count();
		return ns;
	}
};
