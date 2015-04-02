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
