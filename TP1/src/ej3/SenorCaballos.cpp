#include "SenorCaballos.h"

long int dimension;

int main(int argc, char const *argv[])
{
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
		vector<coordenadas> sol = senorCaballos(tablero);
		cout << sol.size() << endl;
		for (int i = 0; i < sol.size(); ++i){
			cout << sol[i].fila+1 << " " << sol[i].col+1 << endl;
		}
//	}
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
	vector<coordenadas> posibles;
	vector<coordenadas> solucion;
//guardamos las casillas libres y les ponemos un caballo
	for(int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			if(!t[i][j].esCaballo/* && t[i][j].ataques == 0*/){
				coordenadas aca;
				aca.fila = i;
 				aca.col = j;
 				posibles.push_back(aca);
 				t[i][j].esCaballo = true;
 			}
		}
	}
	for(int i = 0; i < posibles.size(); ++i){
		atacame(t, posibles[i].fila, posibles[i].col, 1);
	}
	senorCaballosAux(t, posibles, solucion);
	return solucion;
}

//FUNCION MAGICA COMO EL CONQUER DEL EJ2
void senorCaballosAux(Tablero& t, vector<coordenadas>& caballos, vector<coordenadas>& solucion){
	for(int i = caballos.size()-1; i >= 0; --i){
//		imprimir(t);
//		cout << "--------------------------------" << endl;
		coordenadas aca = caballos[i];
		atacame(t, aca.fila, aca.col, -1);
		t[aca.fila][aca.col].esCaballo = false;
		int libres = chequeo(t);
//si hay dos libres, swapeo, si hay 1 o mas de 2, restauro, sino ya lo elimine
		if(libres == 2 || (libres == 1 || libres > 2)){
			if(libres == 2 && !t[aca.fila][aca.col].esCaballo && t[aca.fila][aca.col].ataques == 0)
				aca = ocupaLaLibre(t, aca.fila, aca.col);
			t[aca.fila][aca.col].esCaballo = true;
			atacame(t, aca.fila, aca.col, 1);
			solucion.push_back(aca);
		}
	}
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

coordenadas ocupaLaLibre(Tablero& t, int fila, int col){
	coordenadas res;
	if(fila+2 < dimension){
		if(col+1 < dimension && !t[fila+2][col+1].esCaballo && t[fila+2][col+1].ataques == 0){
			res.fila = fila+2;
			res.col = col+1;
		}
		else if(col-1 >= 0 && !t[fila+2][col-1].esCaballo && t[fila+2][col-1].ataques == 0){
			res.fila = fila+2;
			res.col = col-1;
		}
	}
	if(col+2 < dimension){
		if(fila+1 < dimension && !t[fila+1][col+2].esCaballo && t[fila+1][col+2].ataques == 0){
			res.fila = fila+1;
			res.col = col+2;
		}
		else if(fila-1 >= 0 && !t[fila-1][col+2].esCaballo && t[fila-1][col+2].ataques == 0){
			res.fila = fila-1;
			res.col = col+2;
		}
	}
	if(col-2 >= 0){
		if(fila+1 < dimension && !t[fila+1][col-2].esCaballo && t[fila+1][col-2].ataques == 0){
			res.fila = fila+1;
			res.col = col-2;
		}
		else if(fila-1 >= 0 && !t[fila-1][col-2].esCaballo && t[fila-1][col-2].ataques == 0){
			res.fila = fila-1;
			res.col = col-2;
		}
	}
	if(fila-2 >= 0){
		if(col+1 < dimension && !t[fila-2][col+1].esCaballo && t[fila-2][col+1].ataques == 0){
			res.fila = fila-2;
			res.col = col+1;
		}
		else if(col-1 >= 0 && !t[fila-2][col-1].esCaballo && t[fila-2][col-1].ataques == 0){
			res.fila = fila-2;
			res.col = col-1;
		}
	}
	return res;
}

int chequeo(const Tablero& t){
	int res = 0;
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			if(!t[i][j].esCaballo && t[i][j].ataques == 0){
				res++;
			}
		}
	}
	return res;
}

void imprimir(const Tablero& tablero){
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			cout << tablero[i][j].esCaballo << "(" << tablero[i][j].ataques << ") ";
		}
		cout << endl << endl;
	}
}