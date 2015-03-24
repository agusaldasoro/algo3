#include <iostream>
#include <vector>
#include <math.h>
#include <list>

struct frecuencia{
	int id;
	int costo;
	int principio;
	int fin;
};

void altaFrecuencia(std::vector<frecuencia>& frecuencias);
std::list<frecuencia> divideAndConquer(std::list<frecuencia> frecuencias);
void heapSort(std::vector<>& arreglo);
void minHeapify(std::vector<>& arreglo);
