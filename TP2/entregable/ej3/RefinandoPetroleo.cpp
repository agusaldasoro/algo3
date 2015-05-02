//g++ -o main RefinandoPetroleo.cpp

#include "RefinandoPetroleo.h"

int main(int argc, char const *argv[]){
	unsigned int pozos, cantConexiones, costoRefineria;
	unsigned int pozoA, pozoB, costoTuberia;
	cin >> pozos >> cantConexiones >> costoRefineria;
	vector<eje> ejes;
//leemos la entrada, la almacenamos en ejes
	for (int i = 0; i < cantConexiones; ++i){
		cin >> pozoA >> pozoB >> costoTuberia;
		pozoA--;
		pozoB--;
		eje conex;
		conex.pozoA = pozoA;
		conex.pozoB = pozoB;
		conex.costoTuberia = costoTuberia;
		ejes.push_back(conex);
	}
//aplicamos el algoritmo
	refinandoPetroleo(ejes, pozos, costoRefineria);
	return 0;
}

int refinandoPetroleo(vector<eje>& ejes, int cantPozos, int costoRefineria){
//generamos los arboles minimos para cada componente conexa, en realidad solo los ejes que cuesten menos que poner refinerias
	vector<eje> conexionesMinimas = generarArbolesMinimos(ejes, costoRefineria, cantPozos);
	UnionFind conexos(cantPozos);
	int costoTotal = 0, cantRef = 0;
//armamos un union-find para identificar componentes triviales, en las demas solo hara falta poner una refineria
//en el representante de la componente pues los tubos son mas baratos para unir los distintos pozos
	for (int i = 0; i < conexionesMinimas.size(); ++i) {
		conexos.union_set(conexionesMinimas[i].pozoA, conexionesMinimas[i].pozoB);
		costoTotal += conexionesMinimas[i].costoTuberia;
	}
//en las componentes triviales van refinerias
	vector<bool> refinerias(cantPozos);
	for (int i = 0; i < cantPozos; ++i) {
		if(conexos.find_set(i) == i){
			refinerias[i] = true;
			costoTotal += costoRefineria;
			cantRef += 1;
		}
	}
//cout pedido
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
}

vector<eje> generarArbolesMinimos(vector<eje>& ejes, int costoRefineria, int cantPozos){
	UnionFind bosqueMinimo(cantPozos);
	vector<eje> res;
//ordenamos los ejes segun su costo para obtener en tiempo constante, los menores
	sort(ejes.begin(), ejes.end());
	for (int i = 0; i < ejes.size(); ++i) {
//si agregar el eje no forma ciclo
		if(!bosqueMinimo.is_in(ejes[i].pozoA,ejes[i].pozoB)){
//lo uno y si cuesta menos que poner una refineria, lo agrego a res
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
