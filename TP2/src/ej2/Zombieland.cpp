//g++ -o main Zombieland.cpp

#include "Zombieland.h"

Matriz ciudadInfestada;
unsigned int n, m;
int zombieland(Cubo& grafo, int inicioH, int inicioV, int bunkerH, int bunkerV, int soldados);

int main(int argc, char const *argv[]){
	unsigned int s;
	cin >> n >> m >> s;
	unsigned int inicioH, inicioV, bunkerH, bunkerV;
	cin >> inicioH >> inicioV >> bunkerH >> bunkerV;
	inicioV--;
	inicioH--;
	bunkerV--;
	bunkerH--;
	ciudadInfestada = Matriz(m, vector<pair<int, int> >(n)); //first es derecha, second es abajo
	for (int i = 0; i < m-1; ++i) {
		for (int j = 0; j < n-1; ++j) {
			cin >> ciudadInfestada[i][j].first;
		}
		ciudadInfestada[i][n-1].first = -1;
		for (int j = 0; j < n; ++j) {
			cin >> ciudadInfestada[i][j].second;
		}
	}
	for (int j = 0; j < n-1; ++j) {
		cin >> ciudadInfestada[m-1][j].first;
		ciudadInfestada[m-1][j].second = -1;
	}
	ciudadInfestada[m-1][n-1].first = -1;
	ciudadInfestada[m-1][n-1].second = -1;
	Cubo grafo(m, vector<vector<pair<posYsold, bool> > >(n));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			grafo[i][j] = vector<pair<posYsold, bool> >(s+1);
		}
	}
	cout << zombieland(grafo, inicioH, inicioV, bunkerH, bunkerV, s) << endl;
//	cout << zombiesCuadra(1, 1, ARRIBA) << endl;
//	cout << zombiesCuadra(1, 1, ABAJO) << endl;
//	cout << zombiesCuadra(1, 1, IZQ) << endl;
//	cout << zombiesCuadra(1, 1, DER) << endl;
//	print();
	return 0;
}

int zombieland(Cubo& grafo, int inicioH, int inicioV, int bunkerH, int bunkerV, int soldados){
	int maxSoldados = 0;
	queue<posYsold> cola;
	posYsold actual;
	actual.soldadosVivos = soldados;
	actual.i = inicioH;
	actual.j = inicioV;
	cola.push(actual);
	grafo[inicioH][inicioV][soldados].second = true;
	int zombies;
	int resultadoBatalla;
	while(cola.size() > 0){
		actual = cola.front();
		if(!(actual.i == bunkerH && actual.j == bunkerV)){
			zombies = zombiesCuadra(actual.i, actual.j, ARRIBA);
			resultadoBatalla = resulBatalla(actual.soldadosVivos, zombies);
			if(zombies != -1 && resultadoBatalla > 0 && !grafo[actual.i-1][actual.j][resultadoBatalla].second){
				posYsold arriba;
				arriba.soldadosVivos = resultadoBatalla;
				arriba.i = actual.i-1;
				arriba.j = actual.j;
				cola.push(arriba);
				grafo[actual.i-1][actual.j][resultadoBatalla].second = true;
				grafo[actual.i-1][actual.j][resultadoBatalla].first = actual;
			}
			zombies = zombiesCuadra(actual.i, actual.j, DER);
			resultadoBatalla = resulBatalla(actual.soldadosVivos, zombies);
			if(zombies != -1 && resultadoBatalla > 0 && !grafo[actual.i][actual.j+1][resultadoBatalla].second){
				posYsold der;
				der.soldadosVivos = resultadoBatalla;
				der.i = actual.i;
				der.j = actual.j+1;
				cola.push(der);
				grafo[actual.i][actual.j+1][resultadoBatalla].second = true;
				grafo[actual.i][actual.j+1][resultadoBatalla].first = actual;
			}
			zombies = zombiesCuadra(actual.i, actual.j, ABAJO);
			resultadoBatalla = resulBatalla(actual.soldadosVivos, zombies);
			if(zombies != -1 && resultadoBatalla > 0 && !grafo[actual.i+1][actual.j][resultadoBatalla].second){
				posYsold abajo;
				abajo.soldadosVivos = resultadoBatalla;
				abajo.i = actual.i+1;
				abajo.j = actual.j;
				cola.push(abajo);
				grafo[actual.i+1][actual.j][resultadoBatalla].second = true;
				grafo[actual.i+1][actual.j][resultadoBatalla].first = actual;
			}
			zombies = zombiesCuadra(actual.i, actual.j, IZQ);
			resultadoBatalla = resulBatalla(actual.soldadosVivos, zombies);
			if(zombies != -1 && resultadoBatalla > 0 && !grafo[actual.i][actual.j-1][resultadoBatalla].second){
				posYsold izq;
				izq.soldadosVivos = resultadoBatalla;
				izq.i = actual.i;
				izq.j = actual.j-1;
				cola.push(izq);
				grafo[actual.i][actual.j-1][resultadoBatalla].second = true;
				grafo[actual.i][actual.j-1][resultadoBatalla].first = actual;
			}
		}
		else
			if(maxSoldados < actual.soldadosVivos)
				maxSoldados = actual.soldadosVivos;
		cola.pop();
	}
	return maxSoldados;
}

int zombiesCuadra(int i, int j, movimiento mov){
	switch(mov){
		case ARRIBA:
			if(i == 0)
				return -1;
			return ciudadInfestada[i-1][j].second;
		case ABAJO:
			return ciudadInfestada[i][j].second;
		case IZQ:
			if(j == 0)
				return -1;
			return ciudadInfestada[i][j-1].first;
		case DER:
			return ciudadInfestada[i][j].first;
	}
}

void print(){
	for (int i = 0; i < m-1; ++i) {
		for (int j = 0; j < n-1; ++j) {
			cout << " " << ciudadInfestada[i][j].first;
		}
		cout << endl;
		for (int j = 0; j < n; ++j) {
			cout << ciudadInfestada[i][j].second << " ";
		}
		cout << endl;
	}
	for (int j = 0; j < n-1; ++j) {
		cout << " " << ciudadInfestada[m-1][j].first;
	}
	cout << endl;
}

int resulBatalla(int sold, int zomb){
	if(sold>=zomb)
		return sold;
	return sold-(zomb-sold); 
}