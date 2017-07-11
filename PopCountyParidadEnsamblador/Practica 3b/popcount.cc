//------------------------------------------------------------------------------
// popcount.cc
// http://www.dalkescientific.com/writings/diary/archive/2011/11/02/faster_popcount_update.html
//------------------------------------------------------------------------------

#include <algorithm>  // count generate
#include <chrono>     // now
#include <stdexcept>  // exception runtime_error
#include <iomanip>    // setw
#include <iostream>   // cout endl
#include <iterator>   // ostream_iterator
#include <numeric>    // accumulate iota
#include <random>     // uniform_int_distribution
#include <string>     // string
#include <vector>     // vector

#include "rdtsc.h"    // rdtsc

//------------------------------------------------------------------------------

const unsigned GAP = 12;        // gap between columns
const unsigned SIZE = 1 << 20;  // list size
const unsigned REP = 32;        // how many times we repeat the experiment

unsigned list[SIZE];

//------------------------------------------------------------------------------

unsigned popcount01(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount02(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount03(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount04(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount05(unsigned elem) // from o'hallaron
{
	unsigned count = 0;
	return count & 0xff;
}

//------------------------------------------------------------------------------

unsigned popcount06(unsigned elem) // gustavo
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount07(unsigned x) // from wikipedia
{
	return x;
}

//------------------------------------------------------------------------------

unsigned popcount08(unsigned elem) // by Wegner
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount09(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount10(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount11(unsigned elem)
{
	unsigned count = 0;
	return count;
}

//------------------------------------------------------------------------------

unsigned popcount12(unsigned elem)
{
	return elem;
}

//------------------------------------------------------------------------------

unsigned popcount13(unsigned elem)
{
	return __builtin_popcount(elem);
}

//------------------------------------------------------------------------------

template <class _F> void test (_F & __f, const char *msg)
{
	using namespace std::chrono;
//	using namespace std::chrono_literals; // c++14
//	auto min = 24h;                       // c++14

	uint64_t cycles = std::numeric_limits<uint64_t>::max(), overhead = cycles;

	for (unsigned i = 0; i < REP; ++i)
	{
		uint64_t t1 = rdtsc();
		uint64_t t2 = rdtsc();
		if (t1 < t2 && t2 - t1 < overhead)
			overhead = t2 - t1;
	}

	for (unsigned i = 0; i < REP; ++i)
	{
		uint64_t t1 = rdtsc();
		__f(list[SIZE - 1]);
		uint64_t t2 = rdtsc();
		if (t1 < t2 && t2 - t1 < cycles)
			cycles = t2 - t1;
	}
	cycles -= overhead;

	unsigned result;
	auto min = duration<high_resolution_clock::rep, std::nano>::max(), o2 = min;

	for (unsigned i = 0; i < REP; ++i)
	{
		auto t1 = high_resolution_clock::now();
		auto t2 = high_resolution_clock::now();
		if (t1 < t2 && t2 - t1 < o2)
			o2 = t2 - t1;
	}

	for (unsigned i = 0; i < REP; ++i)
	{
		result = 0;
		auto t1 = high_resolution_clock::now();
		std::for_each(list, list + SIZE, [&](unsigned x){ result += __f(x); });
		auto t2 = high_resolution_clock::now();
		
		if (t2 - t1 < min)
			min = t2 - t1;
	}

	std::cout << msg
	          << std::setw(GAP) << result
	          << std::setw(GAP) << cycles
	          << std::setw(GAP) << std::fixed << std::setprecision(2)
	          << duration_cast<nanoseconds>(min - o2).count() / static_cast<float>(SIZE)
	          << std::setw(GAP) << duration_cast<microseconds>(min).count()
	          << std::endl;
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	try
	{
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_int_distribution<unsigned> distribution;
		auto generator = std::bind(distribution, engine);
		std::generate(list, list + SIZE, generator);

		std::cout <<     "                      "
		          << std::setw(GAP) << "popcnt"
		          << std::setw(GAP) << "cycles"
		          << std::setw(GAP) << "time(ns)"
		          << std::setw(GAP) << "total(us)"
		          << std::endl;

		test(popcount01, "popcount01(for_______)");
		test(popcount02, "popcount02(while_____)");
		test(popcount03, "popcount03(inline____)");
		test(popcount04, "popcount04(inline_v2_)");
		test(popcount05, "popcount05(0'hallaron)");
		test(popcount06, "popcount06(gus_______)");
		test(popcount07, "popcount07(wikipedia_)");
		test(popcount08, "popcount08(Wegner____)");
		test(popcount09, "popcount09(lt8_______)");
		test(popcount10, "popcount10(lt8_v2____)");
		test(popcount11, "popcount11(lt8_v3____)");
		test(popcount12, "popcount12(lt16______)");
		test(popcount13, "popcount13(builtin___)");
	}
	catch(std::exception& e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

//------------------------------------------------------------------------------
