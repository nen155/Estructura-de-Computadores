//-----------------------------------------------------------------------------
// suma64s-h.cc
//-----------------------------------------------------------------------------

#include <iostream>  // std::cout std::endl
#include <limits>    // std::numeric_limits
#include <numeric>   // std::accumulate

//-----------------------------------------------------------------------------

const int N = 9;
int v[N] = {0x1, 0x10, 0x100, 0x1000, 0x10000, 0x100000, 0x1000000, 0x10000000, std::numeric_limits<int>::max()};
long long int resultado = 0;

//-----------------------------------------------------------------------------

long long int suma64s1(int v[], int n)
{
	long long int t = 0;

	while (n--)
		t += *v++;

	return t;
}

//-----------------------------------------------------------------------------

long long int suma64s2(int v[], int n)
{
	long long int t = 0;

	for (int i = 0; i < n; ++i)
		t += v[i];

	return t;
}

//-----------------------------------------------------------------------------

long long int suma64s3(int* primero, int* ultimo)
{
	long long int t = 0;

	while (primero != ultimo)
		t += *primero++;

	return t;
}

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	resultado = suma64s1(v, N);
	std::cout << "suma64s1   = " << resultado << std::endl;

	resultado = suma64s2(v, N);
	std::cout << "suma64s2   = " << resultado << std::endl;

	resultado = suma64s3(v, v + N);
	std::cout << "suma64s3   = " << resultado << std::endl;

	resultado = 0;
	resultado = std::accumulate(&v[0], &v[0] + N, resultado);
	std::cout << "accumulate = " << resultado << std::endl;

	return 0;
}

//-----------------------------------------------------------------------------


