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
	for (int i = 0; i < tamano; ++i) {
		parent[i] = i;
		rank[i] = 0;
	}
}

UnionFind::~UnionFind(){
}

int UnionFind::find_set(int x) {
	if(parent[x] != x)
		parent[x] = find_set(parent[x]);
	return parent[x];
}

void UnionFind::union_set(int x, int y) {
	int rx = find_set(x);
	int ry = find_set(y);
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
