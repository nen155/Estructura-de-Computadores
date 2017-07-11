// line.cc

#include <array>        // array
#include <chrono>       // high_resolution_clock
#include <iomanip>      // setw
#include <iostream>     // cout

using namespace std::chrono;

const unsigned MAXLINE = 1024;
const unsigned GAP = 12;
const unsigned REP = 100;
const unsigned STEPS = 16 * 1024 * 1024; // 16M steps

std::array<int, STEPS> bytes; // STEPS x 4 bytes = 16M x 4B = 64MB

int main()
{
	std::cout << "#" 
	          << std::setw(GAP - 1) << "line (B)"
	          << std::setw(GAP    ) << "time (ms)"
	          << std::endl;

	bytes.fill(0);

	for (unsigned line = 1; line <= MAXLINE; line <<= 1)
	{
		std::array<unsigned, REP> sec;

		for (auto &s: sec)
		{
			auto start = high_resolution_clock::now();
			
			for(unsigned i=0;i<bytes.size();i+=line)
				bytes[i]|=1;

			auto stop = high_resolution_clock::now();

			s = duration_cast<milliseconds>(stop - start).count();
		}

		std::cout << std::setw(GAP) << line * sizeof(int)
		          << std::setw(GAP) << std::fixed << std::setprecision(1)
		          << std::setw(GAP) << *std::min(sec.begin(), sec.end())
		          << std::endl;
	}

	return bytes.front() + bytes.back();
}

