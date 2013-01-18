
/*
#include <boost/config.hpp>
// boost\filesystem

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
//
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
//
using namespace boost::filesystem;
using std::string;
int fs_1(string& _path)
{
	if (!_path.empty())
		std::cout << _path.c_str() << " " << file_size(_path.c_str()) << '\n';

	namespace bf=boost::filesystem;//简单别名  

	//filesystem中最基本的类型  
	bf::path path("/tmp/test");  

	//对当前的目录的操作  
	bf::path old_cpath=bf::current_path(); //取得当前目录  

	bf::path file_path = path / "file"; //path重载了 / 运算符  

	//判断文件存在性  
	if(bf::exists(path))  
	{  
		std::ofstream out(path.file_string().c_str());  
		if(!out) return 1;  
		out << "一个测试文件\n";  
	} else {  
		std::cout << path << "不存在\n";  
		//目录不存在，创建  
		bf::create_directory(path);  
		std::ofstream out(file_path.file_string().c_str());  
		if(!out) return 1;  
		out << "一个测试文件\n";  
	}  

	bf::current_path(path); //设置当前为/home  

	if(bf::is_regular_file(path))  
	{  
		std::cout << path << "是普通文件\n";  
		std::cout << path << ": 大小为" << bf::file_size(path) <<'\n';  
		bf::create_symlink(file_path, "/tmp/test/file-symlink");  
	}   

	bf::current_path(old_cpath);  

	bf::remove(file_path);//删除文件file_path  
	bf::remove_all(path);//递归地删除  

	return 0;
}
*/
#include <iostream>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

void main()
{
	try{
		boost::filesystem::path current_path = boost::filesystem::current_path();
		boost::filesystem::path file_path = current_path / "testfile";
		boost::posix_time::ptime ptime = boost::posix_time::second_clock::local_time();
		if(!boost::filesystem::exists(file_path))
		{
			boost::filesystem::create_directory(file_path);
		}
		string file = file_path.file_string() + "\\test.txt";
		ofstream out(file.c_str());
		out<<ptime;
		cout<<"输出文件内容："<<ptime<<endl;
		out.close();

	}
	catch(exception err)
	{
		cout<<"error"<<endl;
	}
}