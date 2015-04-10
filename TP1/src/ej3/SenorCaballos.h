//COMPILAR! g++ -o main caballos.cpp -std=c++11
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
vector<coordenadas> senorCaballos(Tablero& t);
int senorCaballosAux(Tablero& t, int i, int j, vector<coordenadas>& agregados, vector<coordenadas>& optimoHastaAhora);
void atacame(Tablero& t, int fila, int col, int ataco);
coordenadas ocupaLaLibre(Tablero& t, int fila, int col);
bool chequeo(const Tablero& t);
void imprimir(const Tablero& tablero);
bool sirveAgregar(const Tablero& t, int fila, int col);
