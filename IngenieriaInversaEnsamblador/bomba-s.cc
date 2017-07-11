//------------------------------------------------------------------------
// bomba-s.cc
//------------------------------------------------------------------------

#include <signal.h>
#include <unistd.h>

#include <iostream>
#include <string>

//------------------------------------------------------------------------

void explotar(int)
{
	std::cout << "##########################################" << std::endl
	          << "#           booooooooooooom!!!           #" << std::endl
	          << "##########################################" << std::endl;
	exit(1);
}

//------------------------------------------------------------------------

void desactivar(int)
{
	std::cout << "##########################################" << std::endl
	          << "#         bomba desactivada :)           #" << std::endl
	          << "##########################################" << std::endl;
	exit(0);
}

//------------------------------------------------------------------------

template <typename _t> void comprobar(const _t& buena, const char* msg)
{
	signal(SIGALRM, explotar);
	alarm(5);
	_t clave;
	std::cout << "Introduzca la " << msg << ": ";
	std::cin >> clave;
	if (clave != buena)
		explotar(0);
	signal(SIGALRM, SIG_DFL);
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	int clave2 = 1234;

	comprobar(clave1, "clave1");
	comprobar(clave2, "clave2");
	desactivar(0);
}

//------------------------------------------------------------------------

