#ifndef LISTAADY_H
#define LISTAADY_H

#include <list>
#include <vector>
#include <iostream>

using namespace std;

struct nodoGrado{
	unsigned int nodo;
	unsigned int grado;
	bool operator< (const nodoGrado& otro) const{
		return grado > otro.grado;
	}
};

class listaAdy{
public:
	listaAdy(unsigned int cantNodos);
	~listaAdy();
	void agregarEje(unsigned int a, unsigned int b);
	unsigned int gradoDeNodo(unsigned int nodo);
	unsigned int cantNodos();
	list<unsigned int>* dameVecinos(unsigned int nodo);
	bool sonVecinos(unsigned int a, unsigned int b);
	void ordenar();
	unsigned int esIndependienteMaximal(vector<unsigned int>& conjNodos);
	void imprimirListaAdy();
private:
	vector<list<unsigned int> > lista;
};

listaAdy::listaAdy(unsigned int cantNodos){
	lista = vector<list<unsigned int> >(cantNodos);
}

listaAdy::~listaAdy(){}

unsigned int listaAdy::gradoDeNodo(unsigned int nodo){
	return lista[nodo].size();
}

void listaAdy::agregarEje(unsigned int a, unsigned int b){
	lista[a].push_back(b);
	lista[b].push_back(a);
}

unsigned int listaAdy::cantNodos(){
	return lista.size();
}

list<unsigned int>* listaAdy::dameVecinos(unsigned int nodo){
	return &lista[nodo];
}

void listaAdy::imprimirListaAdy(){
	for (int i = 0; i < lista.size(); ++i)
	{
		cout << "nodo " << i << ": ";
		for (list<unsigned int>::iterator it = lista[i].begin(); it != lista[i].end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

bool listaAdy::sonVecinos(unsigned int a, unsigned int b){
	if(lista[a].size() > lista[b].size()){
		unsigned int z = a;
		a = b;
		b = z;
	}
	for (list<unsigned int>::iterator it = lista[a].begin(); it != lista[a].end(); ++it){
		if(*it == b)
			return true;
	}
	return false;
}

void listaAdy::ordenar(){
	for (int i = 0; i < lista.size(); ++i){
		lista[i].sort();
	}
}

unsigned int listaAdy::esIndependienteMaximal(vector<unsigned int>& conjNodos){
	//marco todos los nodos como no dominados
	vector<bool> maximal(cantNodos());
	//cuento cuantos dominados hay
	unsigned int mirados = 0;
	//por cada nodo en el conjunto
	for (int i = 0; i < conjNodos.size(); ++i){
		unsigned int nodo = conjNodos[i];
		//si ya lo habia marcado como dominado, no es independiente
		if(maximal[nodo])
			return 0;
		//si no lo marco dominado
		maximal[nodo] = true;
		//lo sumo
		mirados++;
		//por cada vecino que tenga
		for (list<unsigned int>::iterator it = dameVecinos(nodo)->begin(); it != dameVecinos(nodo)->end(); ++it){
			//si aun no lo marque, sumo
			if(!maximal[*it])
				mirados++;
			//lo marco
			maximal[*it] = true;
		}
	}
	//si no sume menos que los que hay en total, no es independiente maximal
	if(mirados < maximal.size())
		return 0;
	return conjNodos.size();
}

#endif