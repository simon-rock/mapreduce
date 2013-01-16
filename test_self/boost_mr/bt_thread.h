#include <boost/thread.hpp>
#include <iostream>

void test_thread()
{
	std::cout << "\n" << std::max(1,(int)boost::thread::hardware_concurrency()) << " CPU cores" << std::endl;
}