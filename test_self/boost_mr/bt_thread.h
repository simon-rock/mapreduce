#include <boost/config.hpp>
#include <boost/thread.hpp>
#include <iostream>
// http://www.cnblogs.com/chengmin/archive/2011/12/29/2306416.html
void test_thread()
{
	std::cout << "\n" << std::max(1,(int)boost::thread::hardware_concurrency()) << " CPU cores" << std::endl;
}


// example 1
#include <boost/thread/thread.hpp>
#include <iostream>

void hello()
{
	std::cout <<
		"Hello world, I'm a thread!"
		<< std::endl;
}

int thread_example_1()
{
	boost::thread thrd(&hello);
	thrd.join();
	return 0;
}

// 2 互斥体
// example 2
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

boost::mutex io_mutex;

struct count
{
	count(int id) : id(id) { }

	void operator()()
	{
		for (int i = 0; i < 10; ++i)
		{
			boost::mutex::scoped_lock
				lock(io_mutex);
			std::cout << id << ": "
				<< i << std::endl;
		}
	}

	int id;
};

int thread_example_2()
{
	boost::thread thrd1(count(1));
	boost::thread thrd2(count(2));
	thrd1.join();
	thrd2.join();
	return 0;
}

// example 3
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

// boost::mutex io_mutex;

void count(int id)
{
	for (int i = 0; i < 10; ++i)
	{
		boost::mutex::scoped_lock
			lock(io_mutex);
		std::cout << id << ": " <<
			i << std::endl;
	}
}

int thread_example_3()
{
	boost::thread thrd1(
		boost::bind(&count, 1));
	boost::thread thrd2(
		boost::bind(&count, 2));
	thrd1.join();
	thrd2.join();
	return 0;
}

// 3 条件变量
// example 4
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>

const int BUF_SIZE = 10;
const int ITERS = 100;

// boost::mutex io_mutex;

class buffer
{
public:
	typedef boost::mutex::scoped_lock
		scoped_lock;

	buffer()
		: p(0), c(0), full(0)
	{
	}

	void put(int m)
	{
		scoped_lock lock(mutex);
		if (full == BUF_SIZE)
		{
			{
				boost::mutex::scoped_lock
					lock(io_mutex);
				std::cout <<
					"Buffer is full. Waiting..."
					<< std::endl;
			}
			while (full == BUF_SIZE)
				cond.wait(lock);
		}
		buf[p] = m;
		p = (p+1) % BUF_SIZE;
		++full;
		cond.notify_one();
	}

	int get()
	{
		scoped_lock lk(mutex);
		if (full == 0)
		{
			{
				boost::mutex::scoped_lock
					lock(io_mutex);
				std::cout <<
					"Buffer is empty. Waiting..."
					<< std::endl;
			}
			while (full == 0)
				cond.wait(lk);
		}
		int i = buf[c];
		c = (c+1) % BUF_SIZE;
		--full;
		cond.notify_one();
		return i;
	}

private:
	boost::mutex mutex;
	boost::condition cond;
	unsigned int p, c, full;
	int buf[BUF_SIZE];
};

buffer buf;

void writer()
{
	for (int n = 0; n < ITERS; ++n)
	{
		{
			boost::mutex::scoped_lock
				lock(io_mutex);
			std::cout << "sending: "
				<< n << std::endl;
		}
		buf.put(n);
	}
}

void reader()
{
	for (int x = 0; x < ITERS; ++x)
	{
		int n = buf.get();
		{
			boost::mutex::scoped_lock
				lock(io_mutex);
			std::cout << "received: "
				<< n << std::endl;
		}
	}
}

int thread_example_4()
{
	boost::thread thrd1(&reader);
	boost::thread thrd2(&writer);
	thrd1.join();
	thrd2.join();
	return 0;
}

// 4 线程局部存储
// example 5
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include <iostream>

// boost::mutex io_mutex;
boost::thread_specific_ptr<int> ptr;

struct count_5
{
	count_5(int id) : id(id) { }

	void operator()()
	{
		if (ptr.get() == 0)
			ptr.reset(new int(0));

		for (int i = 0; i < 10; ++i)
		{
			(*ptr)++;
			boost::mutex::scoped_lock
				lock(io_mutex);
			std::cout << id << ": "
				<< *ptr << std::endl;
		}
	}

	int id;
};

int thread_example_5()
{
	boost::thread thrd1(count_5(1));
	boost::thread thrd2(count_5(2));
	thrd1.join();
	thrd2.join();
	return 0;
}

// 5 仅运行一次的例程
// example 6
#include <boost/thread/thread.hpp>
#include <boost/thread/once.hpp>
#include <iostream>

int i = 0;
boost::once_flag flag =
BOOST_ONCE_INIT;

void init()
{
	++i;
}

void thread()
{
	boost::call_once(&init, flag);
}

int thread_example_6()
{
	boost::thread thrd1(&thread);
	boost::thread thrd2(&thread);
	thrd1.join();
	thrd2.join();
	std::cout << i << std::endl;
	return 0;
}


void test_thread_all()
{
	thread_example_1();
	thread_example_2();
	thread_example_3();
	thread_example_4();
	thread_example_5();
	thread_example_6();
}


// http://blog.csdn.net/aimyton/article/details/6871846