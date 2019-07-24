//
// C++11实现的线程池
//

#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>


class threadPool {
public:
	using job = std::function<void()>;

private:
	std::vector<std::thread> _pool;
	std::queue<job> _jobs;
	std::mutex _lock;
	std::condition_variable _cond;
	bool _stop;

public:
	threadPool(int nums = 4) : _stop(false) {
		for(int i = 0; i < nums; ++i) {
			// 使用emplace_back效率更高
			_pool.emplace_back([this]() {
				while( true ) {
					job func;
					{
						std::unique_lock<std::mutex> lock(_lock);
						while(!_stop && _jobs.empty()) {
							_cond.wait(lock);
						}

						if(_stop && _jobs.empty()) {
							return;
						}
						func = _jobs.front();
						_jobs.pop();
					}

					if(func) {
						func();
					}
				}
			});
		}
	}

	void pushJob(const job& func) {
		{
			std::unique_lock<std::mutex> lock(_lock);
			_jobs.push(func);
		}
		_cond.notify_one();
	}

	~threadPool() {
		{
			std::unique_lock<std::mutex> lock(_lock);
			_stop = true;
		}
		_cond.notify_all();
		for(auto& thread : _pool) {
			thread.join();
		}
	}
};
