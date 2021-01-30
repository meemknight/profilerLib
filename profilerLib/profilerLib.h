#pragma once
#include <intrin.h>
#include <Windows.h>

namespace PL 
{
	struct PerfFreqvency
	{
		PerfFreqvency()
		{
			QueryPerformanceFrequency(&perfFreq);
		}

		LARGE_INTEGER perfFreq;
	};

	const static PerfFreqvency freq;



	struct ProfileRezults
	{
		float time;
		float cpuClocks;
	};

	struct SingleProfiler
	{

		LARGE_INTEGER startTime = {};
		__int64 cycleCount = {};

		void start()
		{
			QueryPerformanceCounter(&startTime);
			cycleCount = __rdtsc();
		}

		ProfileRezults end()
		{
			__int64 endCycleCount = __rdtsc();
			LARGE_INTEGER endTime;
			QueryPerformanceCounter(&endTime);

			cycleCount = endCycleCount - cycleCount;
			startTime.QuadPart = endTime.QuadPart - startTime.QuadPart;


			ProfileRezults r = {};

			r.time = (float)startTime.QuadPart / (float)freq.perfFreq.QuadPart;
			r.cpuClocks = cycleCount;

			return r;
		}

	};

	const int AverageProfilerMaxTests = 200;

	struct AverageProfiler
	{
		ProfileRezults rezults[AverageProfilerMaxTests];
		int index = 0;

		SingleProfiler profiler;

		void start()
		{
			profiler.start();
		}

		ProfileRezults end()
		{
			auto r = profiler.end();
			
			if(index < AverageProfilerMaxTests)
			{
				rezults[index] = r;
				index++;
			}

			return r;
		}

		ProfileRezults getAverageNoResetData()
		{
			if (index == 0)
			{
				return { 0,0 };
			}

			long double time;
			unsigned long cpuTime;

			for(int i=0;i<index;i++)
			{
				time += rezults[i].time;
				cpuTime += rezults[i].cpuClocks;
			}


			return { time / (float)index, cpuTime / (float)index };
		}
		
		void resetData()
		{
			index = 0;
		}

		ProfileRezults getAverageAndResetData()
		{
			auto r = getAverageNoResetData();
			resetData();
			return r;
		}


	};
};