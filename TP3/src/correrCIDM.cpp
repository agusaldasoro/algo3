#include <iostream>
#include "exacto_clase.h"
#include "greedy_clase.h"
#include "local_clase.h"
#include "grasp_clase.h"
#include <chrono>

using namespace std;

void mostrar(vector<unsigned int>& optimo){
	cout << optimo.size() << " ";
	for (int i = 0; i < optimo.size(); ++i){
		cout << optimo[i] << " ";
	}
	cout << endl;
}

int main(int argc, char const *argv[]){
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed_seconds;
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
		cout << "6: heuristica grasp percent v1" << endl;
		cout << "7: heuristica grasp percent v2" << endl;
		cout << "8: heuristica grasp cant v1" << endl;
		cout << "9: heuristica grasp cant v2" << endl;
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
		bool greedy, vecindad, conAlpha;
		switch(opcion){
			case '0':
				start = chrono::system_clock::now();
				exactoCIDM(adyacencia, 0, conjNodos, optimo);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optimo);
				break;
			case '1':
				conAlpha = true;
				alpha = 0;
				start = chrono::system_clock::now();
				greedyCIDM(adyacencia, optiGreedy, yaUsados, alpha, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optiGreedy);
				break;
			case '2':
				conAlpha = true;
				greedy = false;
				vecindad = true;
				start = chrono::system_clock::now();
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optiLocal);
				break;
			case '3':
				conAlpha = true;
				greedy = true;
				vecindad = true;
				alpha = 0;
				start = chrono::system_clock::now();
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optiLocal);
				break;
			case '4':
				conAlpha = true;
				greedy = false;
				vecindad = false;
				start = chrono::system_clock::now();
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optiLocal);
				break;
			case '5':
				conAlpha = true;
				greedy = true;
				vecindad = false;
				alpha = 0;
				start = chrono::system_clock::now();
				localCIDM(adyacencia, optiLocal, greedy, vecindad, alpha, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optiLocal);
				break;
			case '6':
				conAlpha = true;
				vecindad = true;
				cout << "con que alpha? ";
				cin >> alpha;
				start = chrono::system_clock::now();
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optimo);
				break;
			case '7':
				conAlpha = true;
				vecindad = false;
				cout << "con que alpha? ";
				cin >> alpha;
				start = chrono::system_clock::now();
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optimo);
				break;
			case '8':
				conAlpha = false;
				vecindad = true;
				cout << "con que alpha? ";
				cin >> alpha;
				start = chrono::system_clock::now();
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
				mostrar(optimo);
				break;
			case '9':
				conAlpha = false;
				vecindad = false;
				cout << "con que alpha? ";
				cin >> alpha;
				start = chrono::system_clock::now();
				graspCIDM(adyacencia, optimo, alpha, vecindad, yaUsados, conAlpha);
				end = chrono::system_clock::now();
				elapsed_seconds = end-start;
				cerr << elapsed_seconds.count() << endl;
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
