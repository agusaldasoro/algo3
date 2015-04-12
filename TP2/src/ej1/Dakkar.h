#include <iostream>
#include <deque>

using namespace std;

struct datosPorEtapas{
	unsigned int bmx;
	unsigned int moto;
	unsigned int buggy;
};

unsigned int dakkar(unsigned int etapas, unsigned int cmoto, unsigned int cbuggy, deque<datosPorEtapas>& datos);