#include <boost/config.hpp>
// elect_platform_config.hpp 分辨操作系统
// #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
// #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
// #  include <boost/smart_ptr/detail/atomic_count_win32.hpp>
// win32.hpp				存放所有 win 宏
// atomic_count_win32.hpp   存放所有 win 宏

#include "bt_thread.h"
#include "bt_fs.h"
#include "bt_numeric_accum.h"

#include <iostream>

// #if defined(BOOST_WINDOWS)
#if defined(ONE)
#define UUU 1
#else 
#define  UUU 2
#endif
int main()
{
	fs_1("main.cpp");
	test_thread();
	test_thread_all();
	test_numeric_accum();
	std::cout << UUU << std::endl;
	return 0;
}