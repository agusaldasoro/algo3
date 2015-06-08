#ifndef LOCAL_CLASE_H
#define LOCAL_CLASE_H

#include <iostream>
#include <vector>
#include "listaAdy.h"


using namespace std;

unsigned int localCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo){
	vector<unsigned int> nodos;
	for (int i = 0; i < adyacencia.cantNodos(); ++i){
		nodos.push_back(i);
	}
	for (vector<unsigned int>::iterator it = nodos.begin(); it != nodos.end(); ++it){
		//asigno al optimo el primero no adyacente a uno ya agregado
		optimo.push_back(*it);
		vector<unsigned int>::iterator iter = it;
		//arranco a mirar desde el siguiente al que estoy parado para eliminar
		iter++;
		while(iter != nodos.end()){
			//si es adyacente lo elimino
			if(adyacencia.sonVecinos(*it, *iter))
				//erase devuelve iterador al siguiente elemento, no hace falta sumar
				iter = nodos.erase(iter);
			else
				iter++;
		}
	}
}

#endif