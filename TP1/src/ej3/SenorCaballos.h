#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

typedef vector<casillero> Vec;
typedef vector<Vec> Tablero;

struct casillero{
	bool esCaballo;
	long int ataques;
};

struct coordenadas{
	unsigned int fila;
	unsigned int col;
};

vector<coordenadas> senorCaballos(Tablero& t);
void senorCaballosAux(Tablero& t, vector<coordenadas>& caballos, vector<coordenadas>& solucion);
//void senorCaballosAux(Tablero& t, Tablero& aux, vector<coordenadas>& solucion);
void atacame(Tablero& t, int fila, int col, int ataco);
coordenadas ocupaLaLibre(Tablero& t, int fila, int col);
int chequeo(const Tablero& t);
void imprimir(const Tablero& tablero);
