#include <vector>

using namespace std;

class UnionFind {
public:
	UnionFind(int tamano);
	~UnionFind();
	int find_set(int x);
	void union_set(int x, int y);
	bool is_in(int x, int y);

private:
	vector<int> parent;
	vector<int> rank;
};

UnionFind::UnionFind(int tamano){
	parent = vector<int>(tamano);
	rank = vector<int>(tamano);
//cada indice es su propio representante, su ranking es 0
	for (int i = 0; i < tamano; ++i) {
		parent[i] = i;
		rank[i] = 0;
	}
}

UnionFind::~UnionFind(){
}

int UnionFind::find_set(int x) {
//si es representante lo devuelvo, si no lo hago apuntar directamente al representante
//para que llamadas consecutivas cuesten tiempo constante
	if(parent[x] != x)
		parent[x] = find_set(parent[x]);
	return parent[x];
}

void UnionFind::union_set(int x, int y) {
//buscamos representantes de ambos elementos
//requiere que no esten en el mismo conjunto
	int rx = find_set(x);
	int ry = find_set(y);
//incluyo el de menor ranking en el de mayor para mantener balanceada la estructura
	if(rank[rx] < rank[ry]){
		parent[rx] = ry;
	}
	else{
		parent[ry] = rx;
		if(rank[ry] == rank[rx])
			rank[rx]++;
	}
}

bool UnionFind::is_in(int x, int y) {
	return find_set(x) == find_set(y);
}
