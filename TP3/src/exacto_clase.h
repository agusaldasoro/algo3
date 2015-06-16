#ifndef EXACTO_CLASE_H
#define EXACTO_CLASE_H

#include <iostream>
#include <vector>
#include "listaAdy.h"
#include <list>

using namespace std;

unsigned int exactoCIDM(listaAdy& adyacencia, unsigned int i, vector<unsigned int>& conjNodos, vector<unsigned int>& optimo){
	unsigned int res = adyacencia.esIndependienteMaximal(conjNodos);
	//si res > 0 es indepte maximal pues sino res == 0
	if (res > 0){
		//modificamos el optimo, si llegamos aqui, es una mejor solucion que la anterior
		optimo.assign(conjNodos.begin(), conjNodos.end());
		return optimo.size();
	}
	unsigned int siAgrego, siNoAgrego;
	//si aun me quedan nodos por mirar
	if(i < adyacencia.cantNodos()){
/*		if(!sirveAgregar(adyacencia, i)){
			return exactoCIDM(adyacencia, i+1, conjNodos, optimo);
		}
*/		
		//poda solucion de mas nodos no me sirve
		if(conjNodos.size() >= optimo.size() - 1)
			return 0;
		//veo que pasa sin agregar
		siNoAgrego = exactoCIDM(adyacencia, i+1, conjNodos, optimo);
		//agrego
		conjNodos.push_back(i);
		//veo que pasa si agrego
		siAgrego = exactoCIDM(adyacencia, i+1, conjNodos, optimo);
		//restauro
		conjNodos.pop_back();
		//devuelvo lo que corresponda
		if(siAgrego == 0 && siNoAgrego == 0)
			return 0;
		if(siNoAgrego == 0 || siAgrego < siNoAgrego)
			return siAgrego;
		return siNoAgrego;
	}
	return 0;
}

#endif