#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<pair<int, int> > > Matriz;

struct posYsold {
	int soldadosVivos;
	int i;
	int j;
};

typedef vector<vector<vector<pair<posYsold, bool> > > > Cubo;

enum movimiento {ARRIBA, ABAJO, IZQ, DER};
void print();
int zombiesCuadra(int i, int j, movimiento mov);
int resulBatalla(int sold, int zomb);
