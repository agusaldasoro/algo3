#ifndef LOCAL_CLASE_H
#define LOCAL_CLASE_H

#include <iostream>
#include <vector>
#include "listaAdy.h"
#include <list>

using namespace std;

struct vecinosEnComun{
	unsigned int nodoA;
	unsigned int nodoB;
	vector<unsigned int> vecinosComun;
};

void completarComunes(list<unsigned int>& vecinos, vector<unsigned int>& comun){
	list<unsigned int>::iterator iter1 = vecinos.begin(), iter2 = vecinos.begin();
	iter2++;
	while(iter2 != vecinos.end()){
		if(*iter1 == *iter2){
			unsigned int copia = *iter1;
			comun.push_back(copia);
		}
		iter1++;
		iter2++;
	}
}

void dameParesVecinosComun(listaAdy& adyacencia, vector<unsigned int>& optimo, vector<vecinosEnComun>& pares){
	for (int i = 0; i < optimo.size(); ++i){
		for (int j = i+1; j < optimo.size(); ++j){
			list<unsigned int> vecinos = *(adyacencia.dameVecinos(optimo[i]));
			list<unsigned int> vecinosB = *(adyacencia.dameVecinos(optimo[j]));
			vecinos.merge(vecinosB);
			vecinosEnComun par;
			par.nodoA = optimo[i];
			par.nodoB = optimo[j];
			par.vecinosComun;
			completarComunes(vecinos, par.vecinosComun);
			if(par.vecinosComun.size() > 0)
				pares.push_back(par);
		}
	}
}

unsigned int localCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo){
	adyacencia.ordenar();
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
	if(optimo.size() == 1)
		return 1;
	if(optimo.size() == 2){
		int i = 0;
		while(i < adyacencia.cantNodos()){
			if(adyacencia.gradoDeNodo(i) == adyacencia.cantNodos()-1){
				optimo.assign(1, i);
				return 1;
			}
			i++;
		}
		return 2;
	}
	bool hayCambiosHechos = true;
	vector<unsigned int> auxiliar = optimo;
	while(hayCambiosHechos){
		vector<vecinosEnComun> pares;
		dameParesVecinosComun(adyacencia, optimo, pares);
		int i = 0;
		while(i < pares.size()){
			if(auxiliar.size() > 1){
				vector<unsigned int>::iterator it = auxiliar.begin();
				while(*it != pares[i].nodoB){
					if(*it == pares[i].nodoA)
						auxiliar.erase(it);
					else
						it++;
				}
				auxiliar.erase(it);
				int j = 0;
				bool esCID = false;
				while(j < pares[i].vecinosComun.size() && !esCID){
					auxiliar.push_back(pares[i].vecinosComun[j]);
					esCID = esIndependienteMaximal(adyacencia, auxiliar);
					if(!esCID){
						auxiliar.pop_back();
						j++;
					}
				}
				if(j != pares[i].vecinosComun.size()){
					optimo = auxiliar;
					i = pares.size();
					hayCambiosHechos = true;
				}
				else
					hayCambiosHechos = false;
				i++;
			}
			else
				i = pares.size();
		}
	}
	return optimo.size();
}

#endif