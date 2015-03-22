#include "Zombieland.h"

int main(int argc, char const *argv[])
{
	int cantCiudades;
	int presupuesto;
	std::vector<ciudad> pais;

//EJEMPLO//////////////////
	cantCiudades = 3;
	presupuesto = 8;
	ciudad c1;
	ciudad c3;
	ciudad c2;
	c1.zombies = 47;
	c1.soldados = 2;
	c1.costo = 4;
	c2.zombies = 15;
	c2.soldados = 1;
	c2.costo = 4;
	c3.zombies = 15;
	c3.soldados = 1;
	c3.costo = 3;
	pais.push_back(c1);
	pais.push_back(c2);
	pais.push_back(c3);
//////////////////////////
	//leer
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
	heapSort(datos);
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

void minHeapify(std::vector<ciudad2>& arreglo){
	int i = arreglo.size()-1;
	int j, k;
	while (i>=0) {
		j=i;
		while (2*j+1<arreglo.size()) {
			k=2*j+1;
			if (2*j+2<arreglo.size() && arreglo[2*j+2].costoTotal < arreglo[k].costoTotal) {
				k=2*j+2;
			}
			if (arreglo[j].costoTotal > arreglo[k].costoTotal) {
				std::swap(arreglo[k], arreglo[j]);
				j = k;
			} else {
				j = arreglo.size();
			}
		}
		i--;
	}
}

void heapSort(std::vector<ciudad2>& arreglo){
	int i = arreglo.size()-1;
	int j, k;
	minHeapify(arreglo);
	while (i>0) {
		std::swap(arreglo[i], arreglo[0]);
		j = 0;
		while (2*j+1<i) {
			k = 2*j+1;
			if (2*j+2<i && arreglo[2*j+2].costoTotal < arreglo[k].costoTotal) {
				k=2*j+2;
			}
			if (arreglo[j].costoTotal > arreglo[k].costoTotal) {
				std::swap(arreglo[k], arreglo[j]);
				j = k;
			} else {
				j = arreglo.size();
			}
		}
		i--;
	}
}