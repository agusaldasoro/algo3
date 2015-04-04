#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

struct casillero{
	bool esCaballo;
	long int ataques;
};

struct coordenadas{
	unsigned int fila;
	unsigned int col;
};

typedef vector<casillero> Vec;
typedef vector<Vec> Tablero;

void atacame(Tablero& t, int fila, int col, int ataco);
void imprimir(const Tablero& tablero);

long int dimension;

int senorCaballos2(Tablero& t);
bool chequeo2(const Tablero& t);

//vector<coordenadas> senorCaballosAux2(Tablero& t, const Tablero& aux, int i, int j){
int senorCaballosAux2(Tablero& t, /*Tablero& aux,*/ int i, int j, int agregados/*, int mejor*/){
	if(chequeo2(t)){
		return agregados;
	}
//	cout << i << " " << j << " " << agregados << endl;
	int agregadosCon, agregadosSin;
	if(i<dimension){
		if(t[i][j].esCaballo){
			j++;
			if(j==dimension){
				j=0; i++;
			}
			return senorCaballosAux2(t, i, j, agregados);
//			agregadosSin = senorCaballosAux2(t, i, j, agregados);
//			agregadosCon = agregados;
		}
		else/* if(i<dimension/* && j<dimension)*/{
			//agrego
			t[i][j].esCaballo = true;
			atacame(t, i, j, 1);
			agregados++;
			if(j<dimension)
				agregadosCon = senorCaballosAux2(t, i, j+1, agregados);
			else
				agregadosCon = senorCaballosAux2(t, i+1, 0, agregados);
			//no lo agrego
			t[i][j].esCaballo = false;
			atacame(t, i, j, -1);
			agregados--;
			if(j<dimension)
				agregadosSin = senorCaballosAux2(t, i, j+1, agregados);
			else
				agregadosSin = senorCaballosAux2(t, i+1, 0, agregados);
		}
		if(agregadosCon==-1 && agregadosSin == -1)
			return -1;
		if(agregadosCon==-1)
			return agregadosSin;
		if(agregadosSin==-1)
			return agregadosCon;
		if(agregadosCon < agregadosSin){
//			cout << "hola ";
			return agregadosCon;
		}
		else{
//			cout << "chau ";
			return agregadosSin;
		}
	}
	else
		return -1;
/*	if(chequeo2(t)){
		if(i==0 && j==0)
			mejor = 0;
		if(agregar < mejor)
			mejor = agregar;
		return mejor;
	}
	//solo modifico posiciones sin caballo
	while(aux[i][j].esCaballo){
		if(j<dimension)
			j++;
		else{
			j=0; i++;
		}
	}
	if(i<dimension && j<dimension){
		//pongo un caballo
		t[i][j].esCaballo = true;
		atacame(t, i, j, 1);
		agregar++;
		//llamo a los demas con este cambio
		int i2 = i;
		for(int j2 = j; j2 <= dimension; ++j2){
			if(j2 == dimension && i2<dimension){
				j2=0; i2++;
			}
			int pongo = senorCaballosAux2(t, aux, i2, j2, agregar, mejor);
		}
		//no pongo un caballo
		atacame(t, i, j, -1);
		t[i][j].esCaballo = false;
		agregar--;
		if(j<dimension)
			int noPongo = senorCaballosAux2(t, aux, i, j+1, agregar, mejor);
		else
			int noPongo = senorCaballosAux2(t, aux, i+1, 0, agregar, mejor);
	}
*/
}

//vector<coordenadas> senorCaballos2(Tablero& t){
int senorCaballos2(Tablero& t){
//calculamos casillas atacadas
	for (int i = 0; i < dimension; ++i){
		for (int j = 0; j < dimension; ++j){
			if(t[i][j].esCaballo){
				atacame(t, i, j, 1);
			}
		}
	}
//	vector<coordenadas> solucion = senorCaballosAux2(t, aux, 0, 0);
//	Tablero aux = t;
	int solucion = senorCaballosAux2(t, /*aux,*/ 0, 0, 0/*, dimension*dimension*/);
	return solucion;
}

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
//		vector<coordenadas> sol = senorCaballos(tablero);
		int sol = senorCaballos2(tablero);
		cout << sol << endl;
//		cout << sol.size() << endl;
//		for (int i = 0; i < sol.size(); ++i){
//			cout << sol[i].fila+1 << " " << sol[i].col+1 << endl;
//		}
//	}
	imprimir(tablero);
	return 0;
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

bool chequeo2(const Tablero& t){
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