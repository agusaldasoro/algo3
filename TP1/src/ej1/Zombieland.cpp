#include "Zombieland.h"

int main(int argc, char const *argv[])
{
	while(true){
		if(std::cin.eof())
			break;
		int cantCiudades;
		int presupuesto;
		std::vector<ciudad> pais;

		std::cin >> cantCiudades;
		std::cin >> presupuesto;
		for (int i = 0; i < cantCiudades; ++i)
		{
			ciudad alguna;
			std::cin >> alguna.zombies;
			std::cin >> alguna.soldados;
			std::cin >> alguna.costo;
			pais.push_back(alguna);
		}
		
		int salvadas = 0;
		std::vector<ciudad2> res = zombieland(cantCiudades, presupuesto, pais, salvadas);
		std::vector<int> entregados(cantCiudades);
		for (int i = 0; i < cantCiudades; ++i)
		{
			entregados[res[i].numCiudad] = res[i].soldadosNecesarios;
		}
		std::cout << salvadas << " ";
		for (int i = 0; i < cantCiudades; ++i)
		{
		std::cout << entregados[i] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}

const std::vector<ciudad2> zombieland(int cantCiudades, int presupuesto, const std::vector<ciudad>& pais, int& salvadas){
	salvadas = 0;
	std::vector<ciudad2> datos;
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
	std::sort_heap(datos.begin(), datos.end());
	for (int i = 0; i < cantCiudades; ++i)
	{
		int dif = presupuesto - datos[i].costoTotal;
		if (dif>=0){
			salvadas++;
			presupuesto = dif;
		}
		else
			datos[i].soldadosNecesarios = 0;
	}
	return datos;
}
