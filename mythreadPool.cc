#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <queue>

struct Task{
	public:
		void *_data;
	public:
		bool setData(void *data){
			_data = data;
		}

		bool Run(){
			srand(time(NULL));
			int sec = rand() % 3;
			printf("id:%p -- run data -- %s -- sleep:%d\n", pthread_self(), _data, sec);
			sleep(sec);
		}
};

class pthreadPool{
	private:
		int _max_thr; //max pthread
		int _cur_thr; //now pthread
		bool _stop_flag; //is stop
		std::queue<Task*> _queue;
		int _cap; //queue capacity
		pthread_mutex_t _lock;
		pthread_cond_t _full;
		pthread_cond_t _empty;
	private:
		bool queueIsFull(){
			return _queue.size() == _cap;
		}

		bool queueIsEmpty(){
			return _queue.empty();
		}

		bool queuePop(Task **task){
			*task = _queue.front();
			_queue.pop();
			return true;
		}

		static void *thrStart(void *arg){
			pthreadPool *pool = (pthreadPool*)arg;

			while(1){
				pthread_mutex_lock(&pool->_lock);
				//queue is empty, wait
				while(pool->queueIsEmpty() && !(pool->_stop_flag)){
					pthread_cond_wait(&pool->_empty, &pool->_lock);
				}

				if(pool->queueIsEmpty() && pool->_stop_flag){
					std::cout << "-pthread eixt-" << std::endl;
					pool->_cur_thr--;
					pthread_mutex_unlock(&pool->_lock);
					pthread_cond_signal(&pool->_full);
					pthread_exit(NULL);
				}

				Task* task;
				pool->queuePop(&task);
				pthread_mutex_unlock(&pool->_lock);
				pthread_cond_signal(&pool->_full);
				task->Run();
			}
		}

	public:
		pthreadPool(int max_thr = 5, int max_queue = 10)
			: _max_thr(max_thr)
			, _cur_thr(0)
			, _stop_flag(false)
			, _cap(max_queue)
		{
			pthread_mutex_init(&_lock, NULL);
			pthread_cond_init(&_full, NULL);
			pthread_cond_init(&_empty, NULL);
		}

		bool initPool(){
			pthread_t tid;
			int i, ret;
			for(i = 0; i < _max_thr; i++){
				ret = pthread_create(&tid, NULL, thrStart, (void*)this);
				if(ret != 0){
					std::cerr << "pthread_create error" << std::endl;
					return false;
				}
				pthread_detach(tid);
			}
		}

		bool addTask(Task *task){
			pthread_mutex_lock(&_lock);
			while(queueIsFull()){
				pthread_cond_wait(&_full, &_lock);
			}
			_queue.push(task);
			pthread_cond_signal(&_empty);
			pthread_mutex_unlock(&_lock);
			return true;
		}

		bool stop(){
			pthread_mutex_lock(&_lock);
			if(_stop_flag){
				pthread_mutex_unlock(&_lock);
				return false;
			}

			_stop_flag = true;
			while(_cur_thr > 0){
				pthread_cond_broadcast(&_empty);
				pthread_cond_wait(&_full, &_lock);
			}
			pthread_mutex_unlock(&_lock);
			return false;
		}

		~pthreadPool(){
			pthread_mutex_destroy(&_lock);
			pthread_cond_destroy(&_full);
			pthread_cond_destroy(&_empty);
		}

};


int main()
{
	pthreadPool pool;
	pool.initPool();
	Task task[10];

	for(int i = 0; i < 10; i++){
		sleep(1);
		task[i].setData((void*)"hello");
		pool.addTask(&task[i]);
	}
	pool.stop();
	return 0;
}
