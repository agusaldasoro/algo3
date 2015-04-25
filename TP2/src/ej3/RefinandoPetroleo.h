#include <iostream>
#include <vector>
#include <algorithm>
#include "UnionFind.h"

using namespace std;

struct eje {
	unsigned int pozoA;
	unsigned int pozoB;
	unsigned int costoTuberia;
	bool operator< (const eje& otro) const{
		return costoTuberia < otro.costoTuberia;
	}
};

int refinandoPetroleo(const UnionFind& grafo, vector<eje>& ejes, int cantPozos, int costoRefineria);
vector<eje> generarArbolesMinimos(const UnionFind& grafo, UnionFind& bosqueMinimo, vector<eje>& ejes, int costoRefineria);
