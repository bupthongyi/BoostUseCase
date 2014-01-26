#include <windows.h>
#include <boost/thread.hpp>

typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost::unique_lock<boost::shared_mutex> writeLock;

bool b_exit = false;
boost::shared_mutex mutex;

void ReadThread1()
{
	while(b_exit == false)
	{
		readLock lock(mutex);
		std::cout << "read test1" << std::endl;
		Sleep(1000);
	}
}

void ReadThread2()
{
	while(b_exit == false)
	{
		readLock lock(mutex);
		std::cout << "read test2" << std::endl;
		Sleep(1000);
	}
}

void ReadThread3()
{
	while(b_exit == false)
	{
		readLock lock(mutex);
		std::cout << "read test3" << std::endl;
		Sleep(1000);
	}
}

void WriteThread1()
{
	while(b_exit == false)
	{
		{
			writeLock lock(mutex); 
			std::cout << "write test" << std::endl;
			Sleep(5000);
		}
		Sleep(5000);
	}
}

int main(int argc, char* argv[])
{
	boost::thread* pthread1 = new boost::thread(boost::bind(&ReadThread1));
	boost::thread* pthread2 = new boost::thread(boost::bind(&ReadThread2));
	boost::thread* pthread3 = new boost::thread(boost::bind(&ReadThread3));
	boost::thread* pthread4 = new boost::thread(boost::bind(&WriteThread1));
	getchar();
	b_exit = true;
	pthread1->join();
	pthread2->join();
	pthread3->join();
	pthread4->join();
	delete pthread1;
	delete pthread2;
	delete pthread3;
	delete pthread4;
	return 0;
}