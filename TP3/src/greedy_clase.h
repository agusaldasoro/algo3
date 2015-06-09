#ifndef GREEDY_CLASE_H
#define GREEDY_CLASE_H

#include <iostream>
#include <vector>
#include "listaAdy.h"
#include <algorithm>


using namespace std;

unsigned int greedyCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo){
	vector<nodoGrado>grados(adyacencia.cantNodos());
	//completo un vector con el nodo y su grado
	for (int i = 0; i < grados.size(); ++i){
		grados[i].nodo = i;
		grados[i].grado = adyacencia.gradoDeNodo(i);
	}
	//ordeno de mayor a menor
	sort(grados.begin(), grados.end());
	//elijo el nodo de mayor grado, elimino a todos sus vecinos, hasta que no pueda elegir mas nodos
	for (vector<nodoGrado>::iterator it = grados.begin(); it != grados.end(); ++it){
		//asigno al optimo el no adyacente a uno ya agregado de grado maximo
		optimo.push_back(it->nodo);
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

#endif