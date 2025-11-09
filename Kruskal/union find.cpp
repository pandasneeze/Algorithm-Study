#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

void makeSet(int n) { //n = 노드의 수
	parent.resize(n);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
}
int find(int x) {
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	else return x;

	return parent[x];
}
void unionSets(int x, int y) { //간선 연결
	int rootX = find(x); //부모 찾기
	int rootY = find(y);

	if (rootX != rootY) { 
		if (rootX < rootY) {
			parent[rootY] = rootX;
		}
		else if (rootX > rootY) {
			parent[rootX] = rootY;
		}
	}
}
