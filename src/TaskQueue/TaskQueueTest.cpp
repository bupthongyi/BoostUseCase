#include <windows.h>
#include <iostream>
#include "TaskQueue.h"

TaskQueue tq;

void Print(std::wstring str)
{
	printf("%d\t%ws\n", GetCurrentThreadId(), str.c_str());
	Sleep(5);
}

void Test()
{
	while(true)
	{
		tq.Post(boost::bind(&Print, L"hello world"));
		Sleep(1000);
	}
}


bool GetCmd()
{
	std::wstring s;
	std::wcin >> s;
	if(s.compare(L"quit") == 0)
	{
		return false;
	}
	else if(s.compare(L"start") == 0)
	{
		tq.Start(10);
	}
	else if(s.compare(L"stop") == 0)
	{
		tq.Stop();
	}
	else if(s.compare(L"pause") == 0)
	{
		tq.Pause();
	}
	else if(s.compare(L"resume") == 0)
	{
		tq.Resume();
	}
	else if(s.compare(L"reset") == 0)
	{
		tq.Reset();
	}
	return true;
}

int main(int argc, char* argv[])
{
	boost::thread* pthread = new boost::thread(boost::bind(&Test));
	std::wcout << L"......\n";
	while(true)
	{
		if (GetCmd() == false)
			break;
	}
	TerminateThread(pthread->native_handle(), 0);
	return 0;
}

