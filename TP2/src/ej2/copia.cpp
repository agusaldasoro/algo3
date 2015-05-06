//g++ -o main copia.cpp

#include "copia.h"

Matriz ciudadInfestada;
unsigned int n, m;

int main(int argc, char const *argv[]){
	unsigned int s;
	cin >> n >> m >> s;
	unsigned int inicioH, inicioV, bunkerH, bunkerV;
	cin >> inicioH >> inicioV >> bunkerH >> bunkerV;
	inicioV--;
	inicioH--;
	bunkerV--;
	bunkerH--;
//la matriz de la ciudad guarda cuantos zombies tiene el eje para moverse a la derecha y hacia abajo (en ese orden)
//para la izquierda es ir al de la izquierda y preguntar por el derecho
//para arriba es ir al de arriba y preguntar por el de abajo
	ciudadInfestada = Matriz(n, vector<pair<int, int> >(m));
	for (int i = 0; i < n-1; ++i) {
		for (int j = 0; j < m-1; ++j) {
			cin >> ciudadInfestada[i][j].first;
		}
//no hay camino a la derecha
		ciudadInfestada[i][m-1].first = -1;
		for (int j = 0; j < m; ++j) {
			cin >> ciudadInfestada[i][j].second;
		}
	}
	for (int j = 0; j < m-1; ++j) {
		cin >> ciudadInfestada[n-1][j].first;
//no hay camino hacia abajo
		ciudadInfestada[n-1][j].second = -1;
	}
//no hay camino a la derecha ni abajo
	ciudadInfestada[n-1][m-1].first = -1;
	ciudadInfestada[n-1][m-1].second = -1;
//	print();
//creamos el cubo a completar
	Cubo grafo(n, vector<vector<pair<posYsold, bool> > >(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			grafo[i][j] = vector<pair<posYsold, bool> >(s+1);
		}
	}
	print();
//aplicamos el algoritmo
	pair<int, bool> soldadosVivos = zombieland(grafo, inicioH, inicioV, bunkerH, bunkerV, s);
//cout pedido
	cout << soldadosVivos.first << endl;
	deque<posYsold> recorrido;
//para armarlo desde el principio hasta el final
	if(soldadosVivos.second){
		posYsold posActual;
		posActual.soldadosVivos = soldadosVivos.first;
		posActual.i = bunkerH;
		posActual.j = bunkerV;
		while(posActual.i != inicioH || posActual.j != inicioV){
			recorrido.push_front(posActual);
			posActual = grafo[posActual.i][posActual.j][posActual.soldadosVivos].first;
		}
		posActual.soldadosVivos = s;
		posActual.i = inicioH;
		posActual.j = inicioV;
		recorrido.push_front(posActual);
	}
	for (int i = 0; i < recorrido.size(); ++i) {
		cout << recorrido[i].i+1 << " " << recorrido[i].j+1 << endl;
	}
	return 0;
}

pair<int, bool> zombieland(Cubo& grafo, int inicioH, int inicioV, int bunkerH, int bunkerV, int soldados){
	pair<int, bool> maxSoldados = make_pair(0, false);
//cola para el BFS arranca con la posicion de donde salimos
	queue<posYsold> cola;
	posYsold actual;
	actual.soldadosVivos = soldados;
	actual.i = inicioH;
	actual.j = inicioV;
	cola.push(actual);
//se marca esta posicion como visitada
	grafo[inicioH][inicioV][soldados].second = true;
	int zombies;
	int resultadoBatalla;
//mientras tengamos algo para visitar (no sabemos si llegaremos al final)
	while(cola.size() > 0){
//actual es el primero de la cola
		actual = cola.front();
	//si no estamos el final vemos si podemos ir a cada una de las cuatro direcciones
	//si es valido, no se mueren todos los soldados y no visite ese nodo, agregare el siguiente nodo a visitar
	//si ya lo visite, existe un camino que me lleva hasta ahi, ya fue encolado el camino que le sigue
		if(!(actual.i == bunkerH && actual.j == bunkerV)){
			zombies = zombiesCuadra(actual.i, actual.j, ARRIBA);
			resultadoBatalla = resulBatalla(actual.soldadosVivos, zombies);
			if(zombies != -1 && resultadoBatalla >= 0 && !grafo[actual.i-1][actual.j][resultadoBatalla].second){
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
			if(zombies != -1 && resultadoBatalla >= 0 && !grafo[actual.i][actual.j+1][resultadoBatalla].second){
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
			if(zombies != -1 && resultadoBatalla >= 0 && !grafo[actual.i+1][actual.j][resultadoBatalla].second){
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
			if(zombies != -1 && resultadoBatalla >= 0 && !grafo[actual.i][actual.j-1][resultadoBatalla].second){
				posYsold izq;
				izq.soldadosVivos = resultadoBatalla;
				izq.i = actual.i;
				izq.j = actual.j-1;
				cola.push(izq);
				grafo[actual.i][actual.j-1][resultadoBatalla].second = true;
				grafo[actual.i][actual.j-1][resultadoBatalla].first = actual;
			}
		}
	//si llegamos al final, actualizamos los soldados que quedaron vivos, si es mayor a haber llegado por otro camino
		else{
			if(maxSoldados.first < actual.soldadosVivos)
				maxSoldados.first = actual.soldadosVivos;
			maxSoldados.second = true;
		}
	//desencolo el nodo que estaba analizando
		cola.pop();
	}
	return maxSoldados;
}

int zombiesCuadra(int i, int j, movimiento mov){
//devuelve los zombies que en la cuadra pedida
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

int resulBatalla(int sold, int zomb){
//devuelve si es posible pasar por una cuadra
	if(sold>=zomb)
		return sold;
	return sold-(zomb-sold); 
}

void print(){
	for (int i = 0; i < n-1; ++i) {
		for (int j = 0; j < m-1; ++j) {
			cout << " " << ciudadInfestada[i][j].first;
		}
		cout << endl;
		for (int j = 0; j < m; ++j) {
			cout << ciudadInfestada[i][j].second << " ";
		}
		cout << endl;
	}
	for (int j = 0; j < m-1; ++j) {
		cout << " " << ciudadInfestada[n-1][j].first;
	}
	cout << endl;
}
