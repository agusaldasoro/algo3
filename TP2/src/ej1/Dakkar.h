#include <iostream>
#include <deque>

using namespace std;

struct datosPorEtapas{
	unsigned int bmx;
	unsigned int moto;
	unsigned int buggy;
};

typedef deque<int> Etapas;
typedef deque<Etapas> Filas;
typedef deque<Filas> Matriz;

unsigned int dakkar(unsigned int etapas, unsigned int cmoto, unsigned int cbuggy, deque<datosPorEtapas>& datos, Matriz cubo, deque<int> decisiones);