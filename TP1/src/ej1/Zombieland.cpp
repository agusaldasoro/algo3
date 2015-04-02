#include "Zombieland.h"
//Hay que compilarlo con el flag -std=c++11

int main(int argc, char const *argv[]){
	chrono::time_point<chrono::system_clock> start, end; //LINEA NUEVA
//	while(true){
//		if(cin.eof())
//			break;
		long int cantCiudades;
		long int presupuesto;
		vector<ciudad> pais;

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
		start = chrono::system_clock::now(); //LINEA NUEVA
		vector<ciudad2> res = zombieland(cantCiudades, presupuesto, pais, salvadas);
		vector<long int> entregados(cantCiudades);
		for (int i = 0; i < cantCiudades; ++i)
		{
			entregados[res[i].numCiudad] = res[i].soldadosNecesarios;
		}
		end = chrono::system_clock::now(); //LINEA NUEVA
		cout << salvadas << " ";
		for (int i = 0; i < cantCiudades; ++i)
		{
		cout << entregados[i] << " ";
		}
		cout << endl;
//	}
	chrono::duration<double> elapsed_seconds = end-start; //LINEA NUEVA
	cout << "Tiempo: " << elapsed_seconds.count() << endl; //LINEA NUEVA
	return 0;
}

const vector<ciudad2> zombieland(long int cantCiudades, long int presupuesto, const vector<ciudad>& pais, long int& salvadas){
	salvadas = 0;
	vector<ciudad2> datos;
	for (int i = 0; i < cantCiudades; ++i)
	{
		ciudad2 actual;
		actual.numCiudad = i;
		double diferencia = (pais[i].zombies - pais[i].soldados * 10);
		if (diferencia > 0)
			actual.soldadosNecesarios = ceil(diferencia/10);
		else
			actual.soldadosNecesarios = 0;
		actual.costoTotal = actual.soldadosNecesarios * pais[i].costo;
		datos.push_back(actual);
	}
	sort(datos.begin(), datos.end());
	long int dif;
	for (int i = 0; i < cantCiudades; ++i)
	{
		dif = presupuesto - datos[i].costoTotal;
		if (dif>=0){
			salvadas++;
			presupuesto = dif;
		}
		else
			datos[i].soldadosNecesarios = 0;
	}
	return datos;
}
