#include <iostream>
#include <vector>
#include <math.h>

struct ciudad{
	int zombies;
	int soldados;
	int costo;
};

struct ciudad2{
	int numCiudad;
	int soldadosNecesarios;
	int costoTotal;
};

const std::vector<ciudad2> zombieland(int cantCiudades, int presupuesto, const std::vector<ciudad>& pais, int& salvadas);
void heapSort(std::vector<ciudad2>& arreglo);
void minHeapify(std::vector<ciudad2>& arreglo);
