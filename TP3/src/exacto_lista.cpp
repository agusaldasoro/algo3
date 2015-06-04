#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef vector<list<unsigned int> > ListaAdy;

void imprimirListaAdy(ListaAdy& adyacencia){
	for (int i = 0; i < adyacencia.size(); ++i)
	{
		cout << "nodo: " << i << " ";
		for (list<unsigned int>::iterator it = adyacencia[i].begin(); it != adyacencia[i].end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

unsigned int esIndependienteMaximal(ListaAdy& adyacencia, vector<unsigned int>& conjNodos){
	vector<bool> maximal(adyacencia.size());
	for (int i = 0; i < conjNodos.size(); ++i){
		unsigned int nodo = conjNodos[i];
		if(maximal[nodo])
			return 0;
		maximal[nodo] = true;
		for (list<unsigned>::iterator it = adyacencia[nodo].begin(); it != adyacencia[nodo].end(); ++it){
			maximal[*it] = true;
		}
	}
	for (int i = 0; i < maximal.size(); ++i){
		if(!maximal[i])
			return 0;
	}
	return conjNodos.size();
}

unsigned int calcularCIDM(ListaAdy& adyacencia, unsigned int i, vector<unsigned int>& conjNodos, vector<unsigned int>& optimo){
	unsigned int res = esIndependienteMaximal(adyacencia, conjNodos);
	if (res > 0){
		optimo.assign(conjNodos.begin(), conjNodos.end());
		return optimo.size();
	}
	unsigned int siAgrego, siNoAgrego;
	if(i < adyacencia.size()){
/*		if(!sirveAgregar(adyacencia, i)){
			return calcularCIDM(adyacencia, i+1, conjNodos, optimo);
		}
*/		if(conjNodos.size() >= optimo.size() - 1)
			return 0;
		siNoAgrego = calcularCIDM(adyacencia, i+1, conjNodos, optimo);
		conjNodos.push_back(i);
		siAgrego = calcularCIDM(adyacencia, i+1, conjNodos, optimo);
		conjNodos.pop_back();
		if(siAgrego == 0 && siNoAgrego == 0)
			return 0;
		if(siNoAgrego == 0 || siAgrego < siNoAgrego)
			return siAgrego;
		return siNoAgrego;
	}
	return 0;
}

int main(int argc, char const *argv[]){
	unsigned int cantNodos, cantEjes, uno, dos;
	cin >> cantNodos >> cantEjes;
	ListaAdy adyacencia(cantNodos, list<unsigned int>());
	for (int i = 0; i < cantEjes; ++i){
		cin >> uno >> dos;
		adyacencia[uno].push_back(dos);
		adyacencia[dos].push_back(uno);
	}
	vector<unsigned int> conjNodos, optimo(cantNodos);
	calcularCIDM(adyacencia, 0, conjNodos, optimo);
	cout << optimo.size() << " ";
	for (int i = 0; i < optimo.size(); ++i){
		cout << optimo[i] << " ";
	}
	cout << endl;
	return 0;
}
