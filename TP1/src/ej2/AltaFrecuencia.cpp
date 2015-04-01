#include <iostream>
#include <vector>
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct frecuencia{
	long int id;
	long int costo;
	long int principio;
	long int fin;
	bool operator< (const frecuencia& otro) const{
//		return costo < otro.costo;
		if (costo < otro.costo)
			return true;
		else if (costo == otro.costo){
			if (principio < otro.principio)
				return true;
			else if (principio == otro.principio)
				return fin > otro.fin;
			else
				return false;
		}else
			return false;
	}
};

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias);
vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, long int comienzo, long int final);
vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara);

//#include "AltaFrecuencia.h"

int main(int argc, char const *argv[])
{
//	while(true){
//		if(cin.eof())
//			break;
		long int cantFrec;
		vector<frecuencia> frecuencias;
		cin >> cantFrec;
		for (int i = 0; i < cantFrec; ++i)
		{
			frecuencia actual;
			actual.id = i;
			cin >> actual.costo;
			cin >> actual.principio;
			cin >> actual.fin;
			if(actual.fin > actual.principio)
				frecuencias.push_back(actual);
		}
		vector<frecuencia> optimas = altaFrecuencia(frecuencias);
		vector<frecuencia>::iterator iter;
		long int costoTotal = 0;
		for (iter = optimas.begin(); iter != optimas.end(); iter++)
		{
			costoTotal += (iter->fin - iter->principio) * iter->costo;
//			cout << "parcial " << (iter->fin - iter->principio) * iter->costo << " costo por minuto " << iter->costo << endl;
//			cout << "acumulado "<< costoTotal << endl;
		}
		cout << costoTotal << endl;
	/*	for (iter = optimas.begin(); iter != optimas.end(); iter++){
			cout << iter->principio << " " << iter->fin << " " << iter->id + 1 << endl;
		}
		cout << "-1" << endl;*/
//	}
	return 0;
}

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias){
	sort(frecuencias.begin(), frecuencias.end());
	return divideAndConquer(frecuencias, 0, frecuencias.size()-1);
}

vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, long int comienzo, long int final){
	if(final - comienzo > 0){
		vector<frecuencia> barata = divideAndConquer(frecuencias, comienzo, (final+comienzo)/2);
		vector<frecuencia> cara = divideAndConquer(frecuencias, ((final+comienzo)/2)+1, final);
		return conquer(barata, cara);
	}
	else{
		vector<frecuencia> res;
		res.push_back(frecuencias[comienzo]);
			return res;
	}
}

vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara){
	vector<frecuencia>::iterator iterCara = cara.begin(), iterBarata = barata.begin();
	// cout << "barata: " << endl;
	// for (vector<frecuencia>::iterator itB = barata.begin(); itB != barata.end(); ++itB){
	// 	cout << '\t' << itB->id + 1 << " principio " << itB->principio << " fin " << itB->fin << endl;
	// }
	// cout << "cara: " << endl;
	// for (vector<frecuencia>::iterator itB = cara.begin(); itB != cara.end(); ++itB){
	// 	cout << '\t' << itB->id + 1 << " principio " << itB->principio << " fin " << itB->fin << endl;
	// }
	vector<frecuencia> res;
	while(iterCara != cara.end()){
		if(iterBarata != barata.end()){
			if(iterCara->principio < iterBarata->principio){ //la cara empieza antes
				if(iterCara->fin <= iterBarata->principio){ //la cara termina antes de que empiece la barata
					res.push_back(*iterCara);				//meto la cara entera
					iterCara++;
				}
				else{ //la cara empieza antes y termina despues del principio de la barata
					frecuencia antes;
					antes.id = iterCara->id;
					antes.costo = iterCara->costo;
					antes.principio = iterCara->principio;
					antes.fin = iterBarata->principio;
					res.push_back(antes);
					iterCara->principio = iterBarata->fin;
				}
			}
			else{ //la barata empieza antes (o igual) que la cara
				if(iterCara->fin > iterBarata->fin){ //la cara termina despues que la barata
					if (iterCara->principio < iterBarata->fin) //este if es nuevo
						iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
					iterCara++;
			}
		}
		else{
			if(iterCara->principio < iterCara->fin)
				res.push_back(*iterCara);
			iterCara++;
		}
	}
	while(iterBarata != barata.end()){
		res.push_back(*iterBarata);
		iterBarata++;
	}
	// cout << "res: " << endl;
	// for (vector<frecuencia>::iterator itB = res.begin(); itB != res.end(); ++itB)
	// {
	// 	cout << '\t' << itB->id + 1 << " principio " << itB->principio << " fin " << itB->fin << endl;
	// }
	return res;
}
