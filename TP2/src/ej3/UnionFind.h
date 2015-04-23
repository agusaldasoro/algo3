#include <vector>

using namespace std;

class UnionFind {
public:
	UnionFind(int tamano);
	~UnionFind();
	int find_set(int x) const;
	void union_set(int x, int y);
	bool is_in(int x, int y) const;
	int cantConexos() const;

private:
	vector<int> parent;
	vector<int> size;
	int disjuntos;
};

UnionFind::UnionFind(int tamano){
	parent = vector<int>(tamano);
	size = vector<int>(tamano);
	disjuntos = tamano;
	for (int i = 0; i < tamano; ++i) {
		parent[i] = i;
		size[i] = 1;
	}
}

UnionFind::~UnionFind(){
}

int UnionFind::find_set(int x) const {
	if(parent[x] == x)
		return x;
	return find_set(parent[x]);
}

void UnionFind::union_set(int x, int y) {
	int rx = find_set(x);
	int ry = find_set(y);
	if(size[rx] > size[ry]){
		parent[ry] = rx;
		size[rx] += size[ry];
	}
	else{
		parent[rx] = ry;
		size[ry] += size[rx];
	}
	disjuntos--;
}

bool UnionFind::is_in(int x, int y) const {
	return find_set(x) == find_set(y);
}

int UnionFind::cantConexos() const {
	return disjuntos;
}