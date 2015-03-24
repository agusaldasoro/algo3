#include "AltaFrecuencia.h"

int main(int argc, char const *argv[])
{
	int cantFrec;
	std::cin >> cantFrec;
	std::vector<frecuencia> frecuencias;
	for (int i = 0; i < cantFrec; ++i)
	{
		frecuencia actual;
		actual.id = i;
		std::cin >> actual.costo;
		std::cin >> actual.principio;
		std::cin >> actual.fin;
		frecuencias.push_back(actual);
	}
	altaFrecuencia(frecuencias);
	return 0;
}

void altaFrecuencia(std::vector<frecuencia>& frecuencias){
	heapSort(frecuencias);
	std::list<frecuencia> optima;
	for (int i = 0; i < frecuencias.size(); ++i)
	{
		optima.push_back(frecuencias[i]);
	}
	std::list<frecuencia> res = divideAndConquer(optima);
}

std::list<frecuencia> divideAndConquer(std::list<frecuencia> frecuencias){
	if (frecuencias.size() > 1)
	{
		list<frecuencias> barata, cara;
		int sizeF = frecuencias.size()/2;
		for (int i = 0; i < sizeF; ++i)
		{
			barata.push_back(frecuencias.front());
			//ojo con la referencia de front!! quizas splice...
			frecuencias.pop_front();
		}
		sizeF = frecuencias.size();
		for (int i = 0; i < sizeF; ++i)
		{
			cara.push_back(frecuencias.front());
			frecuencias.pop_front();
		}
		barata = divideAndConquer(barata);
		cara = divideAndConquer(cara);
		return conquer(barata, cara);
	}
	else
		return frecuencias;
}

std::list<frecuencia> conquer(std::list<frecuencia> barata, std::list<frecuencia> cara){
	std::list<frecuencia>::iterator iterCara, iterBarata;
	for (iterCara = cara.begin(); iterCara.next() != NULL; iterCara++)
	{
		
	}
}

void minHeapify(std::vector<frecuencia>& arreglo){
	int i = arreglo.size()-1;
	int j, k;
	while (i>=0) {
		j=i;
		while (2*j+1<arreglo.size()) {
			k=2*j+1;
			if (2*j+2<arreglo.size() && arreglo[2*j+2].costo < arreglo[k].costo) {
				k=2*j+2;
			}
			if (arreglo[j].costo > arreglo[k].costo) {
				std::swap(arreglo[k], arreglo[j]);
				j = k;
			} else {
				j = arreglo.size();
			}
		}
		i--;
	}
}

void heapSort(std::vector<frecuencia>& arreglo){
	int i = arreglo.size()-1;
	int j, k;
	minHeapify(arreglo);
	while (i>0) {
		std::swap(arreglo[i], arreglo[0]);
		j = 0;
		while (2*j+1<i) {
			k = 2*j+1;
			if (2*j+2<i && arreglo[2*j+2].costo < arreglo[k].costo) {
				k=2*j+2;
			}
			if (arreglo[j].costo > arreglo[k].costo) {
				std::swap(arreglo[k], arreglo[j]);
				j = k;
			} else {
				j = arreglo.size();
			}
		}
		i--;
	}
}