//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"
#include "UnionFind.h"

int refinandoPetroleo(const UnionFind& grafo, vector<eje>& ejes, int cantPozos);
vector<eje> generarArbolesMinimos(const UnionFind& grafo, UnionFind& bosqueMinimo, vector<eje>& ejes);

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos >> cantConexiones >> costoRefineria;
	vector<bool> triviales(pozos);
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
		triviales[pozoA] = true;
		triviales[pozoB] = true;
	}
	refinandoPetroleo(grafo, ejes, pozos);
/*for (int i = 0; i < pozos; ++i) {
	if(!triviales[i])
		cout << "T " << i+1 << " cuesta " << costoRefineria << endl;
}*/
	return 0;
}

int refinandoPetroleo(const UnionFind& grafo, vector<eje>& ejes, int cantPozos){
	UnionFind bosqueMinimo(cantPozos);
	vector<eje> conexionesMinimas = generarArbolesMinimos(grafo, bosqueMinimo, ejes);
/*for (int i = 0; i < conexionesMinimas.size(); ++i) {
	cout << "A " << conexionesMinimas[i].pozoA+1 << " B " << conexionesMinimas[i].pozoB+1 << " cuesta " << conexionesMinimas[i].costoTuberia << endl;
}*/
	
	return 0;
}

vector<eje> generarArbolesMinimos(const UnionFind& grafo, UnionFind& bosqueMinimo, vector<eje>& ejes){
	vector<eje> res;
	sort(ejes.begin(), ejes.end());
	for (int i = 0; i < ejes.size(); ++i) {
		if(bosqueMinimo.find_set(ejes[i].pozoA) != bosqueMinimo.find_set(ejes[i].pozoB)){
			bosqueMinimo.union_set(ejes[i].pozoA, ejes[i].pozoB);
			eje conex;
			conex.pozoA = ejes[i].pozoA;
			conex.pozoB = ejes[i].pozoB;
			conex.costoTuberia = ejes[i].costoTuberia;
			res.push_back(conex);
		}
	}
	return res;
}
