//g++ -o main Dakkar.cpp

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
	Matriz cubo;
	for (int i = 0; i <= cmoto; ++i){
		Filas fila;
		for (int j = 0; j <= cbuggy; ++j){
			Etapas etapa;
			for (int k = 0; k < etapas; ++k){
				etapa.push_back(-1);
			}
			fila.push_back(etapa);
		}
		cubo.push_back(fila);
	}
	cout << dakkar(etapas, cmoto, cbuggy, datos, cubo) << endl;
	return 0;
}

unsigned int dakkar(unsigned int etapas, unsigned int cmoto, unsigned int cbuggy, deque<datosPorEtapas>& datos, Matriz cubo){
	for (int n = 0; n < etapas; ++n){
		for (int m = 0; m <= cmoto; ++m){
			for (int b = 0; b <= cbuggy; ++b){
				if (n==0){
					if(m == 0){
						if(b == 0)
							cubo[m][b][n] = datos[n].bmx;
						else
							cubo[m][b][n] = min(datos[n].bmx, datos[n].buggy);
					}
					else{
						if(b == 0)
							cubo[m][b][n] = min(datos[n].bmx, datos[n].moto);
						else
							cubo[m][b][n] = min(min(datos[n].bmx, datos[n].moto), datos[n].buggy);
					}
				}
				else{
					if(m == 0){
						if(b == 0)
							cubo[m][b][n] = cubo[m][b][n-1] + datos[n].bmx;
						else
							cubo[m][b][n] = min(cubo[m][b][n-1] + datos[n].bmx, cubo[m][b-1][n-1] + datos[n].buggy);
					}
					else{
						if(b == 0)
							cubo[m][b][n] = min(cubo[m][b][n-1] + datos[n].bmx, cubo[m-1][b][n-1] + datos[n].moto);
						else
							cubo[m][b][n] = min(min(cubo[m][b][n-1] + datos[n].bmx, cubo[m-1][b][n-1] + datos[n].moto), cubo[m][b-1][n-1] + datos[n].buggy);
					}
				}
			}
		}
	}
	return cubo[cmoto][cbuggy][etapas-1];
/*	if(etapas == 0) return 0;
	if(cmoto == 0 && cbuggy == 0)
		return datos[etapas-1].bmx + dakkar(etapas-1, cmoto, cbuggy, datos);
	if(cmoto == 0)
		return min(datos[etapas-1].bmx + dakkar(etapas-1, cmoto, cbuggy, datos),
			datos[etapas-1].buggy + dakkar(etapas-1, cmoto, cbuggy - 1, datos));
	if(cbuggy == 0)
		return min(datos[etapas-1].bmx + dakkar(etapas-1, cmoto, cbuggy, datos),
			datos[etapas-1].moto + dakkar(etapas-1, cmoto - 1, cbuggy, datos));
	unsigned int minimo = min(datos[etapas-1].bmx + dakkar(etapas-1, cmoto, cbuggy, datos),
		datos[etapas-1].moto + dakkar(etapas-1, cmoto - 1, cbuggy, datos));
	return min(minimo, datos[etapas-1].buggy + dakkar(etapas-1, cmoto, cbuggy - 1, datos));
*/
}