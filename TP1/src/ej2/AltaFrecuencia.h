#include <iostream>
#include <vector>
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>

using namespace std;

struct frecuencia{
	long int id;
	long int costo;
	long int principio;
	long int fin;
	bool operator< (const frecuencia& otro) const{
		if(costo == otro.costo){
			if(principio == otro.principio)
				return fin > otro.fin;
			return principio < otro.principio;
		}
		return costo < otro.costo;
	}
};

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias);
vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, long int comienzo, long int final);
vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara);
