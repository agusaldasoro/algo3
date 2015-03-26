#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <iterator>
#include <algorithm>

struct frecuencia{
	int id;
	int costo;
	int principio;
	int fin;
	bool operator< (const frecuencia& otro) const{
		return costo < otro.costo;
	}
};

std::list<frecuencia> altaFrecuencia(std::vector<frecuencia>& frecuencias);
std::list<frecuencia> divideAndConquer(std::list<frecuencia> frecuencias);
std::list<frecuencia> conquer(std::list<frecuencia> barata, std::list<frecuencia> cara);
void heapSort(std::vector<frecuencia>& arreglo);
void minHeapify(std::vector<frecuencia>& arreglo);
