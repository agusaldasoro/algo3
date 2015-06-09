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


unsigned int esIndependienteMaximal(listaAdy& adyacencia, vector<unsigned int>& conjNodos){
	vector<bool> maximal(adyacencia.cantNodos());
	for (int i = 0; i < conjNodos.size(); ++i){
		unsigned int nodo = conjNodos[i];
		if(maximal[nodo])
			return 0;
		maximal[nodo] = true;
		for (list<unsigned>::iterator it = adyacencia.dameVecinos(nodo)->begin(); it != adyacencia.dameVecinos(nodo)->end(); ++it){
			maximal[*it] = true;
		}
	}
	for (int i = 0; i < maximal.size(); ++i){
		if(!maximal[i])
			return 0;
	}
	return conjNodos.size();
}

#endif