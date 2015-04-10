//COMPILAR! g++ -o main Zombieland.cpp -std=c++11
#include "Zombieland.h"

int main(int argc, char const *argv[]){
//	chrono::time_point<chrono::system_clock> start, end;
	long int cantCiudades, presupuesto;
	vector<ciudad> pais;
//Leemos informacion del problema
	cin >> cantCiudades;
	cin >> presupuesto;
	for (int i = 0; i < cantCiudades; ++i){
		ciudad alguna;
		cin >> alguna.zombies;
		cin >> alguna.soldados;
		cin >> alguna.costo;
		pais.push_back(alguna);
	}
	long int salvadas = 0;
//	start = chrono::system_clock::now();
//Aplicamos el algoritmo
	vector<ciudad2> res = zombieland(cantCiudades, presupuesto, pais, salvadas);
//	end = chrono::system_clock::now();
	vector<long int> entregados(cantCiudades);
//Stdout pedido
	for (int i = 0; i < cantCiudades; ++i){
		entregados[res[i].numCiudad] = res[i].soldadosNecesarios;
	}
	cout << salvadas << " ";
	for (int i = 0; i < cantCiudades; ++i){
		cout << entregados[i] << " ";
	}
	cout << endl;
//	chrono::duration<double> elapsed_seconds = end-start;
//	cout << "Tiempo: " << elapsed_seconds.count() << endl;
	return 0;
}

const vector<ciudad2> zombieland(long int cantCiudades, long int presupuesto, const vector<ciudad>& pais, long int& salvadas){
	salvadas = 0;
	vector<ciudad2> datos;
	for (int i = 0; i < cantCiudades; ++i){
		ciudad2 actual;
//ID de la ciudad
		actual.numCiudad = i;
//Calculamos el costo de salvar la ciudad i
		double diferencia = (pais[i].zombies - pais[i].soldados * 10);
		if (diferencia > 0)
			actual.soldadosNecesarios = ceil(diferencia/10);
		else
			actual.soldadosNecesarios = 0;
		actual.costoTotal = actual.soldadosNecesarios * pais[i].costo;
//Lo agregamos al vector
		datos.push_back(actual);
	}
//Ordenamos el vector de menor a mayor costo para salvarlas
	sort(datos.begin(), datos.end());
	long int dif = presupuesto;
//Vemos cuantas salvamos respetando el presupuesto
	int i = 0;
	while(i<cantCiudades && dif >= 0){
		dif = presupuesto - datos[i].costoTotal;
		if (dif>=0){
			salvadas++;
			presupuesto = dif;
			++i;
		}
	}
//Las que sobran no se salvan, seteamos los soldados necesarios en 0 para imprimir una respuesta correcta
	while(i<cantCiudades){
		datos[i].soldadosNecesarios = 0;
		++i;
	}
	return datos;
}
