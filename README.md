# profilerLib

Used to time execution of process and cpu clocks.

---

Usage:

Profile time of things.

```cpp

PL::Profiler profiler;
profiler.start();

//do work
Sleep(1000);

auto r = profiler.end();

std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";

```

Make an average of multiple tests.

```cpp

PL::AverageProfiler aProfiler;

	for(int i=0;i<5;i++)
	{
		aProfiler.start();
		Sleep(1000);
		aProfiler.end();
	}

r = aProfiler.getAverageAndResetData();
	std::cout << r.timeSeconds << "  " << r.cpuClocks << "\n";

```

Note that in profilerLib.h you have PROFILER_LIB_AVERAGE_PROFILER_MAX_TESTS macro that sets the max number of profiles for average.
Exciding this number won't crash but just overwrite older values.

Note that in profiler.h you have PROFILER_LIB_REMOVE_IMPLEMENTATION macro that can be set to one to remove the implementation.
calling any profiler.end() will just return PL::ProfileRezults with zeros in timeSeconds and cpuClocks members.

