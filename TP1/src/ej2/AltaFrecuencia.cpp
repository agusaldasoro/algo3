#include "AltaFrecuencia.h"

int main(int argc, char const *argv[])
{
	while(true){
		if(std::cin.eof())
			break;
		int cantFrec;
		std::vector<frecuencia> frecuencias;
		std::cin >> cantFrec;
		for (int i = 0; i < cantFrec; ++i)
		{
			frecuencia actual;
			actual.id = i;
			std::cin >> actual.costo;
			std::cin >> actual.principio;
			std::cin >> actual.fin;
			frecuencias.push_back(actual);
		}
		std::list<frecuencia> optimas = altaFrecuencia(frecuencias);
		std::list<frecuencia>::iterator iter;
		int costoTotal = 0;
		for (iter = optimas.begin(); iter != optimas.end(); iter++)
		{
			costoTotal += (iter->fin - iter->principio) * iter->costo;
		}
		std::cout << costoTotal << std::endl;
		for (iter = optimas.begin(); iter != optimas.end(); iter++){
			std::cout << iter->principio << " " << iter->fin << " " << iter->id << std::endl;
		}
		std::cout << "-1" << std::endl;
	}
	return 0;
}

std::list<frecuencia> altaFrecuencia(std::vector<frecuencia>& frecuencias){
	heapSort(frecuencias);
	std::list<frecuencia> optima;
	for (int i = 0; i < frecuencias.size(); ++i)
	{
		optima.push_front(frecuencias[i]);
	}
	return divideAndConquer(optima);
}

std::list<frecuencia> divideAndConquer(std::list<frecuencia> frecuencias){
	if (frecuencias.size() > 1)
	{
		std::list<frecuencia> barata, cara;
		int sizeF = frecuencias.size()/2;
		for (int i = 0; i < sizeF; ++i)
		{
			barata.push_back(frecuencias.front());
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
	else{
		return frecuencias;
	}
}

std::list<frecuencia> conquer(std::list<frecuencia> barata, std::list<frecuencia> cara){
	std::list<frecuencia>::iterator iterCara = cara.begin(), iterBarata = barata.begin();
	std::list<frecuencia> res;
	while(iterCara != cara.end()){
		if(iterBarata != barata.end()){
			if(iterCara->principio < iterBarata->principio){
				if(iterCara->fin <= iterBarata->principio){
					res.push_back(*iterCara);
					iterCara++;
				}
				else{
					frecuencia antes;
					antes.id = iterCara->id;
					antes.costo = iterCara->costo;
					antes.principio = iterCara->principio;
					antes.fin = iterBarata->principio;
					res.push_back(antes);
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
//no se si es necesario... pero quizas si, si el intervalo queda "negativo" no sirve mas
//					if(iterCara->principio >= iterCara->fin)
//						iterCara++;
				}
			}
			else{
				if(iterCara->fin > iterBarata->fin){
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
//					este push creo que no va, si la cara esta incluida en la barata solo quiero pasar a la siguiente cara
//					res.push_back(*iterBarata);
					iterCara++;
			}
		}
		else{
			res.push_back(*iterCara);
			iterCara++;
		}
	}
	while(iterBarata != barata.end()){
		res.push_back(*iterBarata);
		iterBarata++;
	}
	return res;
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