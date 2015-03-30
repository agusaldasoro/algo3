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
		return costo < otro.costo;
	}
};

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias);
vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, long int comienzo, long int final);
vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara);
