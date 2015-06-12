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
	while(iter2 != vecinos.end()){
		iter2++;
		if(*iter1 == *iter2){
			unsigned int copia = *iter1;
			comun.push_back(copia);
		}
		iter1++;
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

unsigned int localCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, bool greedy, bool vecindad, unsigned int alpha, vector<bool>& yaUsados){
	//ordeno las listas de adyacencias
	adyacencia.ordenar();
	if(greedy){
		greedyCIDM(adyacencia, optimo, yaUsados, alpha);
	}
	else{
		vector<unsigned int> nodos;
		for (int i = 0; i < adyacencia.cantNodos(); ++i){
			nodos.push_back(i);
		}
		for (vector<unsigned int>::iterator it = nodos.begin(); it != nodos.end(); ++it){
			//asigno al optimo el primero no adyacente a uno ya agregado
			optimo.push_back(*it);
			yaUsados[*it] = true;
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

	//si optimo tiene un solo elemento, es CIDM
	if(optimo.size() == 1)
		return 1;
	//si tiene 2, tal vez puede tener uno solo, si existe lo devuelvo, sino es CIDM el de 2
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
	//si n = optimo = adyacencia, entonces hay n componentes conexas, es CIDM
	if(optimo.size() == adyacencia.cantNodos())
		return optimo.size();

	//sino, puedo analizar mejor la primera solucion y buscar CIDM a partir de la misma
	if(vecindad){
		bool hayCambiosHechos = true;
		//copio el optimo para modificarlo
		vector<unsigned int> auxiliar = optimo;
		//mientras encuentre un optimo mejor al anterior
		while(hayCambiosHechos){
			vector<vecinosEnComun> pares;
			//busco los nodos que tienen al menos un vecino en comun y cuales son esos vecinos
			dameParesVecinosComun(adyacencia, optimo, pares);
			//si no hay, no hay mas cambios posibles para optimo
			if(pares.size() == 0)
				hayCambiosHechos = false;
			int i = 0;
			//mientras haya pares
			while(i < pares.size()){
				//guardo una copia de auxuliar para volver atras si fui por un lugar equivocado
				vector<unsigned int> copiaDeSeguridad = auxiliar;
				vector<unsigned int>::iterator it = auxiliar.begin();
				//elimino el par que estoy analizando que tienen al menos un vecino en comun
				while(*it != pares[i].nodoB){
					if(*it == pares[i].nodoA)
						auxiliar.erase(it);
					else
						it++;
				}
				auxiliar.erase(it);
				int j = 0;
				bool esCID = false;
				//mientras tenga vecinos en comun y no haya encontrado un CID
				while(j < pares[i].vecinosComun.size() && !esCID){
					//si aun no use este vecino
					if(!yaUsados[pares[i].vecinosComun[j]]){
						//lo marco usado
						yaUsados[pares[i].vecinosComun[j]] = true;
						vector<unsigned int>::iterator iter = auxiliar.begin();
						//lo agrego en forma ordenada
						while(iter != auxiliar.end() && *iter < pares[i].vecinosComun[j]){
							iter++;
						}
						iter = auxiliar.insert(iter, pares[i].vecinosComun[j]);
						//me fijo si es CID
						esCID = esIndependienteMaximal(adyacencia, auxiliar);
						if(!esCID){
							//si no es lo borro, lo desmarco como usado y reviso el siguiente vecino
							auxiliar.erase(iter);
							yaUsados[pares[i].vecinosComun[j]] = false;
							j++;
						}
					}
					else{
						//si lo use, miro el siguiente
						j++;
					}
				}
				if(esCID){
					//si es CID, sera mejor que el optimo anterior, pues sacamos 2 y agregamos 1
					optimo.assign(auxiliar.begin(), auxiliar.end());
					//termino este ciclo
					i = pares.size();
					//repito con el nuevo optimo
					hayCambiosHechos = true;
				}
				else{
					//si no, restauro auxiliar
					auxiliar = copiaDeSeguridad;
					//eventualmente termino el ciclo principal
					hayCambiosHechos = false;
					//avanzo en este ciclo
					i++;
				}
			}
		}
		return optimo.size();
	}

}

#endif