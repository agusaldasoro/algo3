#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > Matriz;

struct eje {
	unsigned int pozoA;
	unsigned int pozoB;
	unsigned int costoTuberia;
	bool operator< (const eje& otro) const{
		return costoTuberia < otro.costoTuberia;
	}
};