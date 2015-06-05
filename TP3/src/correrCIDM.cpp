#include <iostream>
#include <stdio.h>
#include <unistd.h>	
#include "exacto_clase.h"
#include "greedy_clase.h"

using namespace std;

void mostrar(vector<unsigned int>& optimo){
	cout << optimo.size() << " ";
	for (int i = 0; i < optimo.size(); ++i){
		cout << optimo[i] << " ";
	}
	cout << endl;
}

int main(int argc, char const *argv[]){
	unsigned int cantNodos, cantEjes, uno, dos;
	cin >> cantNodos >> cantEjes;
	listaAdy adyacencia(cantNodos);
	for (int i = 0; i < cantEjes; ++i){
		cin >> uno >> dos;
		adyacencia.agregarEje(uno, dos);
	}
	char opcion;
	while(true){
		cout << endl << "Elija una opcion" << endl;
		cout << "0: algoritmo exacto" << endl;
		cout << "1: heuristica greedy" << endl;
		cout << "2: heuristica busqueda local" << endl;
		cout << "3: heuristica grasp" << endl;
		cout << "i: imprimir lista de aydacencia" << endl;
		cout << "q: salir" << endl;
		cin >> opcion;
		cout << endl;
		vector<unsigned int> conjNodos;
		vector<unsigned int> optimo(cantNodos);
		vector<unsigned int> optiGreedy;
		switch(opcion){
			case '0':
				exactoCIDM(adyacencia, 0, conjNodos, optimo);
				mostrar(optimo);
				break;
			case '1':
				greedyCIDM(adyacencia, optiGreedy);
				mostrar(optiGreedy);
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case 'i':
				adyacencia.imprimirListaAdy();
				break;
			case 'q':
				return 0;
			default:
				cout << "Invalid option, try again" << endl;
		}
	}
	return 0;
}
