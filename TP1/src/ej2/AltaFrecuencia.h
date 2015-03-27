#include <iostream>
#include <vector>
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct frecuencia{
	int id;
	int costo;
	int principio;
	int fin;
	bool operator< (const frecuencia& otro) const{
		return costo < otro.costo;
	}
};

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias);
vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, int comienzo, int final);
vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara);
void heapSort(vector<frecuencia>& arreglo);
void minHeapify(vector<frecuencia>& arreglo);
