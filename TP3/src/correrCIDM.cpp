#include <iostream>
#include <stdio.h>
#include <unistd.h>	
#include "exacto_clase.h"
#include "greedy_clase.h"
#include "local_clase.h"
#include "grasp_clase.h"

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
		cout << "2: heuristica busqueda local init comun v1" << endl;
		cout << "3: heuristica busqueda local init greedy v1" << endl;
		cout << "4: heuristica busqueda local init comun v2" << endl;
		cout << "5: heuristica busqueda local init greedy v2" << endl;
		cout << "6: heuristica grasp construct rand v1" << endl;
		cout << "7: heuristica grasp construct rand v2" << endl;
		cout << "i: imprimir lista de aydacencia" << endl;
		cout << "q: salir" << endl;
		cin >> opcion;
		cout << endl;
		vector<unsigned int> conjNodos;
		vector<unsigned int> optimo;
		for (int i = 0; i < cantNodos; ++i){
			optimo.push_back(i);
		}
		vector<unsigned int> optiGreedy(0);
		vector<bool> yaUsados(adyacencia.cantNodos());
		vector<unsigned int> optiLocal(0);
		unsigned int alpha = 100;
		bool greedy, vecindad;
		switch(opcion){
			case '0':
				exactoCIDM(adyacencia, 0, conjNodos, optimo);
				mostrar(optimo);
				break;
			case '1':
				alpha = 0;
				greedyCIDM(adyacencia, optiGreedy, yaUsados, alpha);
				mostrar(optiGreedy);
				break;
			case '2':
				greedy = false;
				vecindad = true;
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados);
				mostrar(optiLocal);
				break;
			case '3':
				greedy = true;
				vecindad = true;
				alpha = 0;
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados);
				mostrar(optiLocal);
				break;
			case '4':
				greedy = false;
				vecindad = false;
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados);
				mostrar(optiLocal);
				break;
			case '5':
				greedy = true;
				vecindad = false;
				alpha = 0;
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados);
				mostrar(optiLocal);
				break;
			case '6':
				vecindad = true;
				cout << "con que alpha? ";
				cin >> alpha;
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados);
				mostrar(optimo);
				break;
			case '7':
				vecindad = false;
				cout << "con que alpha? ";
				cin >> alpha;
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados);
				mostrar(optimo);
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