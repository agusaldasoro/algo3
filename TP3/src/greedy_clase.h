#ifndef GREEDY_CLASE_H
#define GREEDY_CLASE_H

#include <iostream>
#include <vector>
#include <list>
#include "listaAdy.h"
#include <algorithm>

using namespace std;

unsigned int greedyCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, vector<bool>& yaUsados, unsigned int alpha){
	vector<nodoGrado>grados(adyacencia.cantNodos());
	//completo un vector con el nodo y su grado
	for (int i = 0; i < grados.size(); ++i){
		grados[i].nodo = i;
		grados[i].grado = adyacencia.gradoDeNodo(i);
	}
	//ordeno de mayor a menor
	sort(grados.begin(), grados.end());
//solo para no correr experimentos otra vez, pero alpha = 0 hace greedy comun por como esta armado el algoritmo del else
/*	if(alpha == 0){
		//elijo el nodo de mayor grado, elimino a todos sus vecinos, hasta que no pueda elegir mas nodos
		for (vector<nodoGrado>::iterator it = grados.begin(); it != grados.end(); ++it){
			//asigno al optimo el no adyacente a uno ya agregado de grado maximo
			optimo.push_back(it->nodo);
			yaUsados[it->nodo] = true;
			vector<nodoGrado>::iterator iter = it;
			//arranco a mirar desde el siguiente al que estoy parado para eliminar
			iter++;
			while(iter != grados.end()){
				//si es adyacente lo elimino
				if(adyacencia.sonVecinos(it->nodo, iter->nodo))
					//erase devuelve iterador al siguiente elemento, no hace falta sumar
					iter = grados.erase(iter);
				else
					iter++;
			}
		}
	}
	else{
*/		while(grados.size() > 0){
			unsigned int eleccion = (grados.size()*alpha/100) + 1;
			srand((unsigned) time(NULL));
			unsigned int indice = rand() % eleccion;
			unsigned int nodo = grados[indice].nodo;
			optimo.push_back(nodo);
			yaUsados[nodo] = true;
			vector<nodoGrado>::iterator iter = grados.begin();
			while(iter != grados.end()){
				if(adyacencia.sonVecinos(nodo, iter->nodo) || nodo == iter->nodo)
					iter = grados.erase(iter);
				else
					iter++;
			}
		}
//	}
	sort(optimo.begin(), optimo.end());
	return optimo.size();
}

#endif
