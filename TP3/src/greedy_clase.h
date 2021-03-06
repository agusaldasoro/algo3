#ifndef GREEDY_CLASE_H
#define GREEDY_CLASE_H

#include <iostream>
#include <vector>
#include <list>
#include "listaAdy.h"
#include <algorithm>

using namespace std;

unsigned int greedyCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, vector<bool>& yaUsados, unsigned int alpha, bool conAlpha){
	vector<nodoGrado>grados(adyacencia.cantNodos());
	//completo un vector con el nodo y su grado
	for (int i = 0; i < grados.size(); ++i){
		grados[i].nodo = i;
		grados[i].grado = adyacencia.gradoDeNodo(i);
	}
	//ordeno de mayor a menor
	sort(grados.begin(), grados.end());

	if(conAlpha){
		if(alpha > 100)
			alpha = 100;
		while(grados.size() > 0){
			unsigned int eleccion = (grados.size()*alpha/100) + (alpha == 100 ? 0 : 1);
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
	}
	else{
		if(alpha < 1)
			alpha = 1;
		while(grados.size() > 0){
			if(alpha > grados.size())
				alpha = grados.size();
			srand((unsigned) time(NULL));
			unsigned int indice = rand() % alpha;
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
	}
	return optimo.size();
}

#endif
