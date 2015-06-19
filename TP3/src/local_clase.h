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

struct vecinasEnComun{
	unsigned int nodoA;
	unsigned int nodoB;
	unsigned int nodoC;
	vector<unsigned int> vecinosComun;
};

void dameParesVecinosComun(listaAdy& adyacencia, vector<unsigned int>& optimo, vector<vecinosEnComun>& pares){
	for (int i = 0; i < optimo.size(); ++i){
		for (int j = i+1; j < optimo.size(); ++j){
			list<unsigned int>* vecinosA = adyacencia.dameVecinos(optimo[i]);
			list<unsigned int>* vecinosB = adyacencia.dameVecinos(optimo[j]);
			vecinosEnComun par;
			par.nodoA = optimo[i];
			par.nodoB = optimo[j];
			list<unsigned int>::iterator itVecinosA = vecinosA->begin(), itVecinosB = vecinosB->begin();
			while(itVecinosA != vecinosA->end() && itVecinosB != vecinosB->end()){
				if(*itVecinosA == *itVecinosB){
					par.vecinosComun.push_back(*itVecinosA);
					itVecinosA++;
					itVecinosB++;
				}
				else{
					if(*itVecinosA > *itVecinosB)
						itVecinosB++;
					else
						itVecinosA++;
				}
			}
			if(par.vecinosComun.size() > 0)
				pares.push_back(par);
		}
	}
}

/**
V,E
2E = E(0) + E(1) + ... + E(V-1)
(0,1) => E(0) + E(1)
(0,2) => E(0) + E(2)
...
(0,V-1) => E(0) + E(V-1)
(1,2) => E(1) + E(2)
(1,3) => E(1) + E(3)
...
(1,V-1) => E(1) + E(V-1)
E(0) * (V-1) + E(1) * (V-1) + ... + E(V-1) * (V-1) = 2E * (V-1) = o(EV) = o(V^3)


**/

void dameTernasVecinasComun(listaAdy& adyacencia, vector<unsigned int>& optimo, vector<vecinasEnComun>& ternas){
	for (int i = 0; i < optimo.size(); ++i){
		for (int j = i+1; j < optimo.size(); ++j){
			for (int k = j+1; k < optimo.size(); ++k){
				list<unsigned int>* vecinosA = adyacencia.dameVecinos(optimo[i]);
				list<unsigned int>* vecinosB = adyacencia.dameVecinos(optimo[j]);
				list<unsigned int>* vecinosC = adyacencia.dameVecinos(optimo[k]);
				vecinasEnComun terna;
				terna.nodoA = optimo[i];
				terna.nodoB = optimo[j];
				terna.nodoC = optimo[k];
				list<unsigned int>::iterator itVecinosA = vecinosA->begin(), itVecinosB = vecinosB->begin(), itVecinosC = vecinosC->begin();
				while(itVecinosA != vecinosA->end() && itVecinosB != vecinosB->end() && itVecinosC != vecinosC->end()){
					if(*itVecinosA == *itVecinosB && *itVecinosA == *itVecinosC){
						terna.vecinosComun.push_back(*itVecinosA);
						itVecinosA++;
						itVecinosB++;
						itVecinosC++;
					}
					else if(*itVecinosA < *itVecinosB){
						if(*itVecinosA < *itVecinosC)
							itVecinosA++;
						else
							itVecinosC++;
					}
					else if(*itVecinosB < *itVecinosC)
						itVecinosB++;
					else
						itVecinosC++;
				}
				if(terna.vecinosComun.size() > 0)
					ternas.push_back(terna);
			}
		}
	}
}

unsigned int localCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, bool greedy, bool vecindad, unsigned int alpha, vector<bool>& yaUsados, bool conAlpha){
	//ordeno las listas de adyacencias
	adyacencia.ordenar();
	if(greedy){
		greedyCIDM(adyacencia, optimo, yaUsados, alpha, conAlpha);
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

	sort(optimo.begin(), optimo.end());
	//sino, puedo analizar mejor la primera solucion y buscar CIDM a partir de la misma
	if(vecindad){
		bool hayCambiosHechos = true;
		//copio el optimo para modificarlo
		vector<unsigned int> auxiliar = optimo;
		//mientras encuentre un optimo mejor al anterior
		while(hayCambiosHechos){ //O(V^5)
			vector<vecinosEnComun> pares;
			//busco los nodos que tienen al menos un vecino en comun y cuales son esos vecinos
			dameParesVecinosComun(adyacencia, optimo, pares); // o(EV)
			//si no hay, no hay mas cambios posibles para optimo
			if(pares.size() == 0)
				hayCambiosHechos = false;
			int i = 0;
			//mientras haya pares
			while(i < pares.size()){ // O(V^4)
				//guardo una copia de auxuliar para volver atras si fui por un lugar equivocado
				vector<unsigned int> copiaDeSeguridad = auxiliar;
				vector<unsigned int>::iterator it = auxiliar.begin();
				//elimino el par que estoy analizando que tienen al menos un vecino en comun
				while(*it != pares[i].nodoB){ // O(V)
					if(*it == pares[i].nodoA)
						auxiliar.erase(it);
					else
						it++;
				}
				auxiliar.erase(it);
				int j = 0;
				bool esCID = false;
				//mientras tenga vecinos en comun y no haya encontrado un CID
				while(j < pares[i].vecinosComun.size() && !esCID){ // O(V^2)
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
						esCID = adyacencia.esIndependienteMaximal(auxiliar);
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
	bool hayCambiosHechos = true;
	//copio el optimo para modificarlo
	vector<unsigned int> auxiliar = optimo;
	//mientras encuentre un optimo mejor al anterior
	while(hayCambiosHechos){
		vector<vecinasEnComun> ternas;
		//busco los nodos que tienen al menos un vecino en comun y cuales son esos vecinos
		dameTernasVecinasComun(adyacencia, optimo, ternas);
		//si no hay, no hay mas cambios posibles para optimo
		if(ternas.size() == 0)
			hayCambiosHechos = false;
		int i = 0;
		//mientras haya pares
		while(i < ternas.size()){
			//guardo una copia de auxuliar para volver atras si fui por un lugar equivocado
			vector<unsigned int> copiaDeSeguridad = auxiliar;
			vector<unsigned int>::iterator it = auxiliar.begin();
			//elimino el par que estoy analizando que tienen al menos un vecino en comun
			while(*it != ternas[i].nodoB){
				if(*it == ternas[i].nodoA)
					auxiliar.erase(it);
				else
					it++;
			}
			while(*it != ternas[i].nodoC){
				if(*it == ternas[i].nodoB)
					auxiliar.erase(it);
				else
					it++;
			}
			auxiliar.erase(it);
			int j = 0;
			bool esCID = false;
			//mientras tenga vecinos en comun y no haya encontrado un CID
			while(j < ternas[i].vecinosComun.size() && !esCID){
				//si aun no use este vecino
				if(!yaUsados[ternas[i].vecinosComun[j]]){
					//lo marco usado
					yaUsados[ternas[i].vecinosComun[j]] = true;
					vector<unsigned int>::iterator iter = auxiliar.begin();
					//lo agrego en forma ordenada
					while(iter != auxiliar.end() && *iter < ternas[i].vecinosComun[j]){
						iter++;
					}
					iter = auxiliar.insert(iter, ternas[i].vecinosComun[j]);
					//me fijo si es CID
					esCID = adyacencia.esIndependienteMaximal(auxiliar);
					if(!esCID){
						//si no es lo borro, lo desmarco como usado y reviso el siguiente vecino
						auxiliar.erase(iter);
						yaUsados[ternas[i].vecinosComun[j]] = false;
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
				i = ternas.size();
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

#endif