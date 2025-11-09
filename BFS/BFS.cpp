#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const vector<vector<int>> graph = {
	{1,2},
	{0,3,4},
	{0,5},
	{1},
	{1},
	{2}
};

void bfs(int start) {
	int n = graph.size();
	vector<bool> visited;
	for (int i = 0; i < n; i++) {
		visited.push_back(false); //모두 false로 초기화
	}
	queue<int> q;

	visited[start] = true;
	q.push(start);

	while (!q.empty()) { //큐가 빌 때까지
		int x = q.front();
		q.pop();
		cout << x << " ";

		for (int i = 0; i < graph[x].size(); i++) {
			int y = graph[x][i];
			if (!visited[y]) {
				q.push(y);
				visited[y] = true;
			}//if
		}//for
	}//while
}

int main() {
	int start;
	cin >> start;

	bfs(start);
}
