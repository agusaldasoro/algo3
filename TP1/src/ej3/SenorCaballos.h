#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <iterator>
#include <algorithm>
#include <chrono>

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

//vector<coordenadas> senorCaballos(Tablero& t);
//int senorCaballos(Tablero& t);
vector<coordenadas> senorCaballos(Tablero& t);
//void senorCaballosAux(Tablero& t, vector<coordenadas>& caballos, vector<coordenadas>& solucion);
//void senorCaballosAux(Tablero& t, Tablero& aux, vector<coordenadas>& solucion);
//int senorCaballosAux(Tablero& t, int i, int j, int agregados);
vector<coordenadas> senorCaballosAux(Tablero& t, int i, int j, vector<coordenadas>& agregados, int& optimoHastaAhora);
void atacame(Tablero& t, int fila, int col, int ataco);
coordenadas ocupaLaLibre(Tablero& t, int fila, int col);
bool chequeo(const Tablero& t);
//int chequeo(const Tablero& t);
void imprimir(const Tablero& tablero);
