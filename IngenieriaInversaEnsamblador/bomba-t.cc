//------------------------------------------------------------------------
// bomba-t.cc
//------------------------------------------------------------------------

#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

//------------------------------------------------------------------------

void explotar()
{
	std::cout << std::endl
	          << "##########################################" << std::endl
	          << "#            booooooooooooom!!!          #" << std::endl
	          << "##########################################" << std::endl;
	exit(1);
}

//------------------------------------------------------------------------

void desactivar()
{
	std::cout << std::endl
	          << "##########################################" << std::endl
	          << "#          bomba desactivada :)          #" << std::endl
	          << "##########################################" << std::endl;
	exit(0);
}

//------------------------------------------------------------------------

template<typename _tipo> void comparar(const _tipo& viejo, const char* msg)
{
	std::atomic<bool> bomba_armada;

	std::thread t([&]
	{
		bomba_armada = true;
		auto fin = std::chrono::high_resolution_clock::now() + 
		           std::chrono::seconds(5);
		while (bomba_armada.load())
		{
			std::this_thread::yield();
			if (std::chrono::high_resolution_clock::now() > fin)
				explotar();
		}
	});

	std::cout << "Introduzca " << msg << ": ";
	_tipo nuevo;
	std::cin >> nuevo;
	if (nuevo != viejo)
		explotar();

	bomba_armada = false;
	t.join();
}

//------------------------------------------------------------------------

int main()
{
	std::string clave1 = "hola";
	int clave2 = 1234;

	comparar(clave1, "clave1");
	comparar(clave2, "clave2");
	desactivar();
}

//------------------------------------------------------------------------

