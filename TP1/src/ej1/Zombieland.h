#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct ciudad{
	long int zombies;
	long int soldados;
	long int costo;
};

struct ciudad2{
	long int numCiudad;
	long int soldadosNecesarios;
	long int costoTotal;
	bool operator< (const ciudad2& otro) const{
		return costoTotal < otro.costoTotal;
	}
};

const std::vector<ciudad2> zombieland(long int cantCiudades, long int presupuesto, const std::vector<ciudad>& pais, long int& salvadas);
