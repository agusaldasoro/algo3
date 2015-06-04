#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool> > Matriz;

void imprimirMatriz(Matriz& adyacencia){
	for (int i = 0; i < adyacencia.size(); ++i){
		for (int j = 0; j < adyacencia.size(); ++j)
			cout << adyacencia[i][j];
		cout << endl;
	}
}

unsigned int esIndependienteMaximal(Matriz& adyacencia, vector<unsigned int>& conjNodos){
	vector<bool> maximal(adyacencia.size());
	for (int i = 0; i < conjNodos.size(); ++i){
		for (int j = i+1; j < conjNodos.size(); ++j){
			if (adyacencia[conjNodos[i]][conjNodos[j]])
				return 0;
		}
		maximal[conjNodos[i]] = true;
		for (int k = 0; k < adyacencia.size(); ++k){
			if (adyacencia[conjNodos[i]][k])
				maximal[k] = true;
		}
	}
	for (int i = 0; i < maximal.size(); ++i){
		if(!maximal[i])
			return 0;
	}
	return conjNodos.size();
}

unsigned int calcularCIDM(Matriz& adyacencia, unsigned int i, vector<unsigned int>& conjNodos, vector<unsigned int>& optimo){
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
	Matriz adyacencia(cantNodos, vector<bool>(cantNodos));
	for (int i = 0; i < cantEjes; ++i){
		cin >> uno >> dos;
		adyacencia[uno][dos] = true;
		adyacencia[dos][uno] = true;
	}
	vector<unsigned int> conjNodos, optimo(cantNodos);
//	imprimirMatriz(adyacencia);
	calcularCIDM(adyacencia, 0, conjNodos, optimo);
	cout << optimo.size() << " ";
	for (int i = 0; i < optimo.size(); ++i){
		cout << optimo[i] << " ";
	}
	cout << endl;
	return 0;
}

