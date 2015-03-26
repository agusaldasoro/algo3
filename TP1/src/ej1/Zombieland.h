#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

struct ciudad{
	int zombies;
	int soldados;
	int costo;
};

struct ciudad2{
	int numCiudad;
	int soldadosNecesarios;
	int costoTotal;
	bool operator< (const ciudad2& otro) const{
		return costoTotal < otro.costoTotal;
	}
};

const std::vector<ciudad2> zombieland(int cantCiudades, int presupuesto, const std::vector<ciudad>& pais, int& salvadas);
