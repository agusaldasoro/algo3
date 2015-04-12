#include "Dakkar.h"

int main(int argc, char const *argv[]){
	unsigned int etapas, cmoto, cbuggy;
	cin >> etapas >> cmoto >> cbuggy;
	deque<datosPorEtapas> datos;
	for (int i = 0; i < etapas; ++i){
		unsigned int bmx, moto, buggy;
		datosPorEtapas actual;
		cin >> actual.bmx >> actual.moto >> actual.buggy;
		datos.push_back(actual);
	}
	cout << dakkar(etapas, cmoto, cbuggy, datos) << endl;
	return 0;
}

unsigned int dakkar(unsigned int etapas, unsigned int cmoto, unsigned int cbuggy, deque<datosPorEtapas>& datos){
	if(etapas == 0) return 0;
	if(cmoto == 0 && cbuggy == 0) return datos[etapas-1].bmx + dakkar(etapas-1, 0, 0, datos);
	if(cmoto == 0) return min(datos[etapas-1].bmx + dakkar(etapas-1, 0, cbuggy, datos), datos[etapas-1].buggy + dakkar(etapas-1, 0, cbuggy - 1, datos));
	if(cbuggy == 0) return min(datos[etapas-1].bmx + dakkar(etapas-1, cmoto, 0, datos), datos[etapas-1].moto + dakkar(etapas-1, cmoto - 1, 0, datos));
	unsigned int minimo = min(datos[etapas-1].bmx + dakkar(etapas-1, 0, cbuggy, datos), datos[etapas-1].moto + dakkar(etapas-1, cmoto - 1, 0, datos));
	return min(minimo, datos[etapas-1].buggy + dakkar(etapas-1, 0, cbuggy - 1, datos));
}