#include <boost/config.hpp>
// elect_platform_config.hpp �ֱ����ϵͳ
// #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
// #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
// #  include <boost/smart_ptr/detail/atomic_count_win32.hpp>
// win32.hpp				������� win ��
// atomic_count_win32.hpp   ������� win ��

#include "bt_thread.h"
#include <iostream>

// #if defined(BOOST_WINDOWS)
#if defined(ONE)
#define UUU 1
#else 
#define  UUU 2
#endif
int main()
{
	test_thread();
	std::cout << UUU << std::endl;
	return 0;
}