//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos, cantConexiones, costoRefineria;
	deque<conectados> conexiones;
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA, pozoB, costoTuberia;
		conectados conex;
		conex.pozoA = pozoA;
		conex.pozoB = pozoB;
		conex.costo = costoTuberia;
		conexiones.push_back(conex);
	}
	return 0;
}
