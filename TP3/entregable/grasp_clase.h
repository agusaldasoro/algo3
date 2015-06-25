#ifndef GRASP_CLASE_H
#define GRASP_CLASE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "listaAdy.h"

using namespace std;

unsigned int graspCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, unsigned int alpha, bool vecindad, vector<bool>& yaUsados, bool conAlpha){
	int repeticiones = 0;
	//mientras no actualicemos el optimo X veces consecutivas
	while(repeticiones < 10){
		vector<unsigned int> optimoAux;
		//genero solucion inicial randomnizada y le aplico busqueda local
		localCIDM(adyacencia, optimoAux, true, vecindad, alpha, yaUsados, conAlpha);
		//corri una vez y no mejore el optimo
		repeticiones++;
		//si en realidad lo hice
		if(optimoAux.size() < optimo.size()){
			//asigno el nuevo optimo y vuelvo a contar repeticiones
			optimo.assign(optimoAux.begin(), optimoAux.end());
			repeticiones = 0;
		}
	}
	return optimo.size();
}

#endif