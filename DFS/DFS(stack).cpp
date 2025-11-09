#include <iostream>
#include <stack>
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

void dfs(int start) {
	int n = graph.size();
	vector<bool> visited;
	for (int i = 0; i < n; i++) {
		visited.push_back(false);
	}

	stack<int> s;
	s.push(start); //시작 노드 삽입

	while (!s.empty()) {
		int x = s.top();
		s.pop();

		if (!visited[x]) { 
			visited[x] = true;
			cout << x << " ";

			for (int i = graph[x].size() - 1; i >= 0; i--) {
				int next = graph[x][i];
				if (!visited[next]) {
					s.push(next);
				}//if
			}//for
		}//if
	}//while
}

int main() {
	dfs(0);
}
