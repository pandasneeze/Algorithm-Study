#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph = {
	{1,2},
	{0,3,4},
	{0,5},
	{1},
	{1},
	{2}
};
vector<bool> visited; //전역 변수 또는 main내에 넣어서 dfs에 call by reference해야함

void dfs(int start) { 
	visited[start] = true; //스택에 삽입 후 방문 처리
	cout << start << " ";

	for (int i = 0; i < graph[start].size(); i++) { //작은 수의 노드부터
		int x = graph[start][i];
		if (!visited[x]) { //방문하지 않은 인접 노드가 있는 경우
			dfs(x);
		}
	}
}

int main() {
	for (int i = 0; i < 6; i++) {
		visited.push_back(false);
	}
	dfs(0);
}
