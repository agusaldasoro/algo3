//COMPILAR! g++ -o main SenorCaballos.cpp -std=c++11
#include "SenorCaballos.h"

long int dimension;

int main(int argc, char const *argv[]){
	chrono::time_point<chrono::system_clock> start, end;
	long int cantCaballos;
	cin >> dimension;
	cin >> cantCaballos;
//Creamos un tablero sin caballos
	Tablero tablero(dimension, Vec(dimension));
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			casillero actual;
			actual.esCaballo = false;
			actual.ataques = 0;
			tablero[i][j] = actual;
		}
	}
//Leemos informacion del problema
	int fila;
	int col;
	for (int i = 0; i < cantCaballos; ++i){
		cin >> fila;
		cin >> col;
//Agregamos los caballos y las posiciones a las que ataca
		tablero[fila-1][col-1].esCaballo = true;
		atacame(tablero, fila-1, col-1, 1);
	}
	
	start = chrono::system_clock::now();
//Aplicamos el algoritmo
	vector<coordenadas> sol = senorCaballos(tablero);
	end = chrono::system_clock::now();
//Stdout pedido
	cout << sol.size() << endl;
	for (int i = 0; i < sol.size(); ++i){
		cout << sol[i].fila+1 << " " << sol[i].col+1 << endl;
	}
//	for (int i = 0; i < sol.size(); ++i){
//		tablero[sol[i].fila][sol[i].col].esCaballo = true;
//		atacame(tablero, sol[i].fila, sol[i].col, 1);
//	}
//	imprimir(tablero);
	chrono::duration<double> elapsed_seconds = end-start;
	cout << "Tiempo: " << elapsed_seconds.count() << endl;
	return 0;
}

vector<coordenadas> senorCaballos(Tablero& t){
//Creamos un vector de n*n, con n = dimension del tablero, "la peor manera de cubrir un tablero es colocando un caballo en cada casillero"
	coordenadas aca;
	vector<coordenadas> optimo;
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			aca.fila = i; aca.col = j;
			optimo.push_back(aca);
		}
	}
//Creamos el vector solucion
	vector<coordenadas> agregados;
	senorCaballosAux(t, 0, 0, agregados, optimo);
	return optimo;
}

int senorCaballosAux(Tablero& t, int i, int j, vector<coordenadas>& agregados, vector<coordenadas>& optimo){
	if(chequeo(t)){
		optimo.assign(agregados.begin(),agregados.end());
		return agregados.size();
	}
	// chequeo = false
	int siAgrego, siNoAgrego;
	if(i<dimension){
		if(t[i][j].esCaballo){
			j++;
			if(j==dimension){
				j=0; i++;
			}
			return senorCaballosAux(t, i, j, agregados, optimo);
		}
		else{
			if(agregados.size() == optimo.size()-1 || (!sirveAgregar(t, i, j) && t[i][j].ataques > 0))
				return -1;
			//no lo agrego
			if(j<dimension-1)
				siNoAgrego = senorCaballosAux(t, i, j+1, agregados, optimo);
			else
				siNoAgrego = senorCaballosAux(t, i+1, 0, agregados, optimo);
			//agrego
			t[i][j].esCaballo = true;
			atacame(t, i, j, 1);
			coordenadas aca;
			aca.fila = i; aca.col = j;
			agregados.push_back(aca);
			if(j<dimension-1)
				siAgrego = senorCaballosAux(t, i, j+1, agregados, optimo);
			else
				siAgrego = senorCaballosAux(t, i+1, 0, agregados, optimo);
			//restauro
			t[i][j].esCaballo = false;
			atacame(t, i, j, -1);
			agregados.pop_back();
		}
		if(siAgrego == -1 && siNoAgrego == -1)
			return -1;
		if(siNoAgrego==-1 || siAgrego < siNoAgrego)
			return siAgrego;
		return siNoAgrego;
	}
	else
		return -1;
}

//ataco = 1 ataca, ataco = -1 desataca
void atacame(Tablero& t, int fila, int col, int ataco){
	if(col-2 >= 0){
		if(fila-1 >= 0) t[fila-1][col-2].ataques += ataco;
		if(fila+1 < dimension) t[fila+1][col-2].ataques += ataco;
	}
	if(col+2 < dimension){
		if(fila-1 >= 0) t[fila-1][col+2].ataques += ataco;
		if(fila+1 < dimension) t[fila+1][col+2].ataques += ataco;
	}
	if(fila-2 >= 0){
		if(col-1 >= 0) t[fila-2][col-1].ataques += ataco;
		if(col+1 < dimension) t[fila-2][col+1].ataques += ataco;
	}
	if(fila+2 < dimension){
		if(col-1 >= 0) t[fila+2][col-1].ataques +=ataco;
		if(col+1 < dimension) t[fila+2][col+1].ataques +=ataco;
	}
}

bool chequeo(const Tablero& t){
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			if(!t[i][j].esCaballo && t[i][j].ataques == 0){
				return false;
			}
		}
	}
	return true;
}

void imprimir(const Tablero& tablero){
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			cout << tablero[i][j].esCaballo << "(" << tablero[i][j].ataques << ") ";
		}
		cout << endl << endl;
	}
}

bool sirveAgregar(const Tablero& t, int fila, int col){
	if(col-2 >= 0){
		if(fila-1 >= 0 && t[fila-1][col-2].ataques == 0 && !(t[fila-1][col-2].esCaballo))
			return true;
		if(fila+1 < dimension && t[fila+1][col-2].ataques == 0 && !(t[fila+1][col-2].esCaballo))
			return true;
	}
	if(col+2 < dimension){
		if(fila-1 >= 0 && t[fila-1][col+2].ataques == 0 && !(t[fila-1][col+2].esCaballo))
			return true;
		if(fila+1 < dimension && t[fila+1][col+2].ataques == 0 && !(t[fila+1][col+2].esCaballo)) 
			return true;
	}
	if(fila-2 >= 0){
		if(col-1 >= 0 && t[fila-2][col-1].ataques == 0 && !(t[fila-2][col-1].esCaballo)) 
			return true;
		if(col+1 < dimension && t[fila-2][col+1].ataques == 0 && !(t[fila-2][col+1].esCaballo))
			return true;
	}
	if(fila+2 < dimension){
		if(col-1 >= 0 && t[fila+2][col-1].ataques == 0 && !(t[fila+2][col-1].esCaballo)) 
			return true;
		if(col+1 < dimension && t[fila+2][col+1].ataques == 0 && !(t[fila+2][col+1].esCaballo)) 
			return true;
	}
	return false;
}