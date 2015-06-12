#ifndef GRASP_CLASE_H
#define GRASP_CLASE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "listaAdy.h"

using namespace std;

unsigned int graspCIDM(listaAdy& adyacencia, vector<unsigned int>& optimo, unsigned int alpha, bool vecindad, vector<bool>& yaUsados){
	int repeticiones = 0;
	while(repeticiones < 5){
		vector<unsigned int> optimoAux;
		localCIDM(adyacencia, optimoAux, true, vecindad, alpha, yaUsados);
		repeticiones++;
		if(optimoAux.size() < optimo.size()){
			optimo.assign(optimoAux.begin(), optimoAux.end());
			repeticiones = 0;
		}
	}
	return optimo.size();
}

#endif