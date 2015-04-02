#include "SenorCaballos.h"
//Hay que compilarlo con el flag -std=c++11

long int dimension;

int main(int argc, char const *argv[]){
	chrono::time_point<chrono::system_clock> start, end; //LINEA NUEVA
//	while(true){
//		if(cin.eof())
//			break;
		long int cantCaballos;
		cin >> dimension;
		cin >> cantCaballos;

		Tablero tablero(dimension, Vec(dimension));
		for (int i = 0; i < dimension; ++i){
			for (int j = 0; j < dimension; ++j){
				casillero actual;
				actual.esCaballo = false;
				actual.ataques = 0;
				tablero[i][j] = actual;
			}
		}
		int fila;
		int col;
		for (int i = 0; i < cantCaballos; ++i){
			cin >> fila;
			cin >> col;
			tablero[fila-1][col-1].esCaballo = true;
		}
		
		start = chrono::system_clock::now(); //LINEA NUEVA
		//vector<coordenadas> sol = senorCaballos(tablero);
		vector<coordenadas> sol = senorCaballos(tablero);
		end = chrono::system_clock::now(); //LINEA NUEVA
		cout << sol.size() << endl;
		for (int i = 0; i < sol.size(); ++i){
			cout << sol[i].fila+1 << " " << sol[i].col+1 << endl;
		}
		for (int i = 0; i < sol.size(); ++i){
			tablero[sol[i].fila][sol[i].col].esCaballo = true;
			atacame(tablero, sol[i].fila, sol[i].col, 1);
		}
//	}
	imprimir(tablero);
	chrono::duration<double> elapsed_seconds = end-start; //LINEA NUEVA
	cout << "Tiempo: " << elapsed_seconds.count() << endl; //LINEA NUEVA
	return 0;
}

vector<coordenadas> senorCaballos(Tablero& t){
//calculamos casillas atacadas
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			if(t[i][j].esCaballo){
				atacame(t, i, j, 1);
			}
		}
	}
//	int solucion = senorCaballosAux(t, 0, 0, 0);
	vector<coordenadas> agregados;
	int optimo = dimension*dimension;
	vector<coordenadas> solucion = senorCaballosAux(t, 0, 0, agregados, optimo);
	return solucion;
}

vector<coordenadas> senorCaballosAux(Tablero& t, int i, int j, vector<coordenadas>& agregados, int& optimo){
	vector<coordenadas> res(optimo+1);
	if(chequeo(t)){
		if(agregados.size() < optimo)
			optimo = agregados.size();
//		cerr << optimo << " ";	
		return agregados;
	}
//	cout << i << " " << j << " " << agregados << endl;
	vector<coordenadas> agregadosCon, agregadosSin;
	if(i<dimension){
		if(t[i][j].esCaballo){
			j++;
			if(j==dimension){
				j=0; i++;
			}
			return senorCaballosAux(t, i, j, agregados, optimo);
//			agregadosSin = senorCaballosAux2(t, i, j, agregados);
//			agregadosCon = agregados;
		}
		else{
			if(agregados.size() == optimo)
				return res;
			//agrego
			t[i][j].esCaballo = true;
			atacame(t, i, j, 1);
			coordenadas aca;
			aca.fila = i; aca.col = j;
			agregados.push_back(aca);
			if(j<dimension-1)
				agregadosCon = senorCaballosAux(t, i, j+1, agregados, optimo);
			else
				agregadosCon = senorCaballosAux(t, i+1, 0, agregados, optimo);
			t[i][j].esCaballo = false;
			atacame(t, i, j, -1);
			agregados.pop_back();
			if(j<dimension-1)
				agregadosSin = senorCaballosAux(t, i, j+1, agregados, optimo);
			else
				agregadosSin = senorCaballosAux(t, i+1, 0, agregados, optimo);
		}
		if(agregadosCon.size() > optimo && agregadosSin.size() > optimo)
			return res;
		if(agregadosCon.size() > optimo){
			return agregadosSin;
		}
		if(agregadosSin.size() > optimo){
			return agregadosCon;
		}
		if(agregadosCon.size() < agregadosSin.size()){
			return agregadosCon;
		}
		return agregadosSin;
	}
	return res;
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