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
//iniciliazamos el cubo
	for (int i = 0; i <= cmoto; ++i){
		Filas fila;
		for (int j = 0; j <= cbuggy; ++j){
			Etapas etapa;
			for (int k = 0; k < etapas; ++k){
				etapa.push_back(make_pair(0, make_pair(0, 0)));
			}
			fila.push_back(etapa);
		}
		cubo.push_back(fila);
	}
//cout pedido
	cout << dakkar(etapas, cmoto, cbuggy, datos, cubo);
//para devolver del comienzo hasta el final
	deque<int> usados;
	pair<int, int> recorrido;
	int cantMoto = cmoto, cantBuggy = cbuggy;
	for (int cantE = etapas-1; cantE >= 0; --cantE) {
		recorrido = cubo[cantMoto][cantBuggy][cantE].second;
		if(cantMoto > recorrido.first){
			cantMoto--;
			usados.push_front(2);
		}
		else if(cantBuggy > recorrido.second){
			cantBuggy--;
			usados.push_front(3);
		}
		else{
			usados.push_front(1);
		}
	}
	for (int i = 0; i < etapas; ++i) {
		cout << " " << usados[i];
	}
	cout << endl;
	return 0;
}

unsigned int dakkar(unsigned int etapas, unsigned int cmoto, unsigned int cbuggy, deque<datosPorEtapas>& datos, Matriz& cubo){
	int bici, moto, buggy;
	for (int n = 0; n < etapas; ++n){
		for (int m = 0; m <= cmoto; ++m){
			for (int b = 0; b <= cbuggy; ++b){
			//guardamos un link hacia el lugar de donde salimos
				pair<int, int> par;
				par.first = m;
				par.second = b;
			//llenamos espacios triviales y luego sabemos cuales estan calculados, para ahorrar rehacer las cuentas
				if (n==0){
					if(m == 0){
						if(b == 0){
							bici = datos[n].bmx;
							cubo[m][b][n] = make_pair(bici, par);
						}
						else{
							bici = datos[n].bmx;
							buggy = datos[n].buggy;
						//si elegimos el buggy guardamos esa decision
							if(bici > buggy)
								par.second--;
							cubo[m][b][n] = make_pair(min(bici, buggy), par);
						}
					}
					else{
						if(b == 0){
							bici = datos[n].bmx;
							moto = datos[n].moto;
						//si elegimos la moto guardamos esa decision
							if(bici > moto)
								par.first--;
							cubo[m][b][n] = make_pair(min(bici, moto), par);
						}
						else{
							bici = datos[n].bmx;
							moto = datos[n].moto;
							buggy = datos[n].buggy;
						//guardamos lo que elegimos
							if(bici > buggy || bici > moto)
								if(buggy > moto)
									par.first--;
								else
									par.second--;
							cubo[m][b][n] = make_pair(min(min(bici, moto), buggy), par);
						}
					}
				}
				else{
					if(m == 0){
						if(b == 0){
							bici = cubo[m][b][n-1].first + datos[n].bmx;
							cubo[m][b][n] = make_pair(bici, par);
						}
						else{
							bici = cubo[m][b][n-1].first + datos[n].bmx;
							buggy = cubo[m][b-1][n-1].first + datos[n].buggy;
						//si elegimos el buggy guardamos esa decision
							if(bici > buggy)
								par.second--;
							cubo[m][b][n] = make_pair(min(bici, buggy), par);
						}
					}
					else{
						if(b == 0){
							bici = cubo[m][b][n-1].first + datos[n].bmx;
							moto = cubo[m-1][b][n-1].first + datos[n].moto;
						//si elegimos la moto guardamos esa decision
							if(bici > moto)
								par.first--;
							cubo[m][b][n] = make_pair(min(bici, moto), par);
						}
						else{
							bici = cubo[m][b][n-1].first + datos[n].bmx;
							moto = cubo[m-1][b][n-1].first + datos[n].moto;
							buggy = cubo[m][b-1][n-1].first + datos[n].buggy;
						//guardamos lo que elegimos
							if(bici > buggy || bici > moto)
								if(buggy > moto)
									par.first--;
								else
									par.second--;
							cubo[m][b][n] = make_pair(min(min(bici, moto), buggy), par);
						}
					}
				}
			}
		}
	}
	return cubo[cmoto][cbuggy][etapas-1].first;
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