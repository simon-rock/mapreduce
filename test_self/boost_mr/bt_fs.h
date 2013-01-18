
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

	namespace bf=boost::filesystem;//�򵥱���  

	//filesystem�������������  
	bf::path path("/tmp/test");  

	//�Ե�ǰ��Ŀ¼�Ĳ���  
	bf::path old_cpath=bf::current_path(); //ȡ�õ�ǰĿ¼  

	bf::path file_path = path / "file"; //path������ / �����  

	//�ж��ļ�������  
	if(bf::exists(path))  
	{  
		std::ofstream out(path.file_string().c_str());  
		if(!out) return 1;  
		out << "һ�������ļ�\n";  
	} else {  
		std::cout << path << "������\n";  
		//Ŀ¼�����ڣ�����  
		bf::create_directory(path);  
		std::ofstream out(file_path.file_string().c_str());  
		if(!out) return 1;  
		out << "һ�������ļ�\n";  
	}  

	bf::current_path(path); //���õ�ǰΪ/home  

	if(bf::is_regular_file(path))  
	{  
		std::cout << path << "����ͨ�ļ�\n";  
		std::cout << path << ": ��СΪ" << bf::file_size(path) <<'\n';  
		bf::create_symlink(file_path, "/tmp/test/file-symlink");  
	}   

	bf::current_path(old_cpath);  

	bf::remove(file_path);//ɾ���ļ�file_path  
	bf::remove_all(path);//�ݹ��ɾ��  

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
		cout<<"����ļ����ݣ�"<<ptime<<endl;
		out.close();

	}
	catch(exception err)
	{
		cout<<"error"<<endl;
	}
}