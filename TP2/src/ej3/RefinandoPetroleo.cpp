//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"
#define INFINITO 2^64

void generarArbolMinimo(const Matriz& grafo, Matriz& arboles);
int refinandoPetroleo(const Matriz& grafo);

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos >> cantConexiones >> costoRefineria;
	Matriz grafo;
	for (int i = 0; i < pozos; ++i) {
		grafo.push_back(deque<pair<int, int> >(pozos));
	}
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA >> pozoB >> costoTuberia;
		grafo[pozoA-1][pozoB-1] = make_pair(costoTuberia, 1);
		grafo[pozoB-1][pozoA-1] = make_pair(costoTuberia, 1);
	}
	refinandoPetroleo(grafo);
	return 0;
}

int refinandoPetroleo(const Matriz& grafo){
	Matriz arbolesGeneradores;
	for (int i = 0; i < grafo.size(); ++i) {
		arbolesGeneradores.push_back(deque<pair<int, int> >(grafo.size()));
	}
	generarArbolMinimo(grafo, arbolesGeneradores);
	for (int i = 0; i < grafo.size(); ++i) {
		for (int j = 0; j < grafo.size(); ++j) {
			cout << arbolesGeneradores[i][j].first << " ";
		}
		cout << endl;
	}
	return 0;
}

void generarArbolMinimo(const Matriz& grafo, Matriz& arboles){
	deque<int> seConectoCon;
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
