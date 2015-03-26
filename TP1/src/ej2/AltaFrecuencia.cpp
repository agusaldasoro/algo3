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
	sort_heap(frecuencias.begin(), frecuencias.end());
	std::list<frecuencia> optima;
	for (int i = 0; i < frecuencias.size(); ++i)
	{
		optima.push_back(frecuencias[i]);
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
				}
			}
			else{
				if(iterCara->fin > iterBarata->fin){
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
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
