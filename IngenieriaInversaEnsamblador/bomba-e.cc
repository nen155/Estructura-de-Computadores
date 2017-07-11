//------------------------------------------------------------------------
// bomba-s.cc
//------------------------------------------------------------------------

#include <chrono>
#include <iostream>
#include <string>

//------------------------------------------------------------------------

std::string explotar = "##########################################\n"\
                       "#           booooooooooooom!!!           #\n"\
                       "##########################################",
          desactivar = "##########################################\n"\
                       "#         bomba desactivada :)           #\n"\
                       "##########################################";

//------------------------------------------------------------------------

template <typename _t> void comprobar(const _t& buena, const char* msg)
{
	auto t0 = std::chrono::high_resolution_clock::now();
	_t clave;
	std::cout << "Introduzca la " << msg << ": ";
	std::cin >> clave;
	auto t = std::chrono::high_resolution_clock::now() - t0;
	if (clave != buena || 
	    std::chrono::duration_cast<std::chrono::seconds>(t).count() > 5)
		throw explotar;
}

//------------------------------------------------------------------------

int main()
{
	try
	{
		std::string clave1 = "hola";
		int clave2 = 1234;

		comprobar(clave1, "clave1");
		comprobar(clave2, "clave2");
		throw desactivar;
	}
	catch(std::string& s)
	{
		std::cout << s << std::endl;
	}
}

//------------------------------------------------------------------------

