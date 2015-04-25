//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos >> cantConexiones >> costoRefineria;
	vector<eje> ejes;
	UnionFind grafo(pozos);
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA >> pozoB >> costoTuberia;
		pozoA--;
		pozoB--;
		if(!grafo.is_in(pozoA, pozoB))
			grafo.union_set(pozoA, pozoB);
		eje conex;
		conex.pozoA = pozoA;
		conex.pozoB = pozoB;
		conex.costoTuberia = costoTuberia;
		ejes.push_back(conex);
	}
	int res = refinandoPetroleo(grafo, ejes, pozos, costoRefineria);
	return 0;
}

int refinandoPetroleo(const UnionFind& grafo, vector<eje>& ejes, int cantPozos, int costoRefineria){
	UnionFind bosqueMinimo(cantPozos);
	vector<eje> conexionesMinimas = generarArbolesMinimos(grafo, bosqueMinimo, ejes, costoRefineria);
	UnionFind conexos(cantPozos);
	int costoTotal = 0, cantRef = 0;
	for (int i = 0; i < conexionesMinimas.size(); ++i) {
		conexos.union_set(conexionesMinimas[i].pozoA, conexionesMinimas[i].pozoB);
		costoTotal += conexionesMinimas[i].costoTuberia;
	}
	vector<bool> refinerias(cantPozos);
	for (int i = 0; i < cantPozos; ++i) {
		if(conexos.find_set(i) == i){
			refinerias[i] = true;
			costoTotal += costoRefineria;
			cantRef += 1;
		}
	}
	cout << costoTotal << " " << cantRef << " " << conexionesMinimas.size() << endl;
	for (int i = 0; i < refinerias.size(); ++i) {
		if(refinerias[i])
			cout << i+1 << " ";
	}
	cout << endl;
	for (int i = 0; i < conexionesMinimas.size(); ++i) {
		cout << conexionesMinimas[i].pozoA+1 << " " << conexionesMinimas[i].pozoB+1 << endl;
	}
	return costoTotal;
	return 0;
}

vector<eje> generarArbolesMinimos(const UnionFind& grafo, UnionFind& bosqueMinimo, vector<eje>& ejes, int costoRefineria){
	vector<eje> res;
	sort(ejes.begin(), ejes.end());
	for (int i = 0; i < ejes.size(); ++i) {
		if(!bosqueMinimo.is_in(ejes[i].pozoA,ejes[i].pozoB)){
			bosqueMinimo.union_set(ejes[i].pozoA, ejes[i].pozoB);
			if(ejes[i].costoTuberia < costoRefineria){
				eje conex;
				conex.pozoA = ejes[i].pozoA;
				conex.pozoB = ejes[i].pozoB;
				conex.costoTuberia = ejes[i].costoTuberia;
				res.push_back(conex);
			}
		}
	}
	return res;
}
