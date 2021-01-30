#include <Windows.h>
#include <iostream>

#include "profilerLib.h"

int main()
{

	PL::Profiler profiler;

	profiler.start();

	Sleep(1000);

	auto r = profiler.end();

	std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";
	
	PL::AverageProfiler aProfiler;

	for(int i=0;i<5;i++)
	{
		aProfiler.start();
		Sleep(1000);
		aProfiler.end();
	}
	
	r = aProfiler.getAverageAndResetData();
	std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";

	system("pause");

	return 0;
}