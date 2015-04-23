//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"
#include "UnionFind.h"
#define INFINITO 2^64

void generarArbolMinimo(const Matriz& grafo, Matriz& arboles);
int refinandoPetroleo(const UnionFind& grafo, int componente, const Matriz& costos);

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos >> cantConexiones >> costoRefineria;
/*	Matriz grafo;
	for (int i = 0; i < pozos; ++i) {
		grafo.push_back(vector<pair<int, int> >(pozos));
	}
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA >> pozoB >> costoTuberia;
		grafo[pozoA-1][pozoB-1] = make_pair(costoTuberia, 1);
		grafo[pozoB-1][pozoA-1] = make_pair(costoTuberia, 1);
	}
*/
	Matriz costos(pozos, vector<int>(pozos));
	UnionFind grafo(pozos);
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA >> pozoB >> costoTuberia;
		pozoA--;
		pozoB--;
		if(!grafo.is_in(pozoA, pozoB))
			grafo.union_set(pozoA, pozoB);
		costos[pozoA][pozoB] = costoTuberia;
	}
	vector<int> conexos;
	for (int i = 0; i < pozos; ++i) {
		if(grafo.find_set(i) == i)
			conexos.push_back(i);
	}
	for (int i = 0; i < grafo.cantConexos(); ++i) {
		refinandoPetroleo(grafo, conexos[i], costos);
	}
	return 0;
}

int refinandoPetroleo(const UnionFind& grafo, int componente, const Matriz& costos){
//	generarArbolMinimo(grafo, arbolesGeneradores);
	return 0;
}
/*
void generarArbolMinimo(const Matriz& grafo, Matriz& arboles){
	vector<int> seConectoCon;
	for (int i = 0; i < grafo.size(); ++i) {
		seConectoCon.push_back(i);
	}
	int ejes = 1;
	while (ejes < grafo.size()) {
		int minimo = INFINITO, x, y;
		for (int i = 0; i < grafo.size(); ++i) {
			for (int j = 0; j < grafo.size(); ++j) {
				if(minimo > grafo[i][j].first && grafo[i][j].second != 0 && seConectoCon[i] != seConectoCon[j]){
					minimo = grafo[i][j].first;
					x = i;
					y = j;
				}
			}
		}
		if(seConectoCon[x] != seConectoCon[y]){
			arboles[x][y].first = minimo;
			arboles[y][x].first = minimo;
			int aux = seConectoCon[y];
			for (int k = 0; k < grafo.size(); ++k) {
				if(seConectoCon[k] == aux)
					seConectoCon[k] = seConectoCon[x];
			}
			ejes++;
		}
	}
}
*/