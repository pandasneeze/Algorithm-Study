#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void dfs(int start, const vector<vector<int>>& graph);
void bfs(int start, const vector<vector<int>>& graph);
int main() {
	int n, m, v; //정점, 간선, 시작
	cin >> n >> m >> v;

	vector<vector<int>> graph(n + 1);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		graph[x].push_back(y);
		graph[y].push_back(x); //양방향이므로!!
	}

	for (int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	dfs(v, graph);
	cout << endl;
	bfs(v, graph);

}
void dfs(int start, const vector<vector<int>>& graph) {

	stack<int> s;
	vector<bool> visited(graph.size() + 1);
	s.push(start);

	while (!s.empty()) {
		int j = s.top();
		s.pop();

		if (!visited[j]) {
			visited[j] = true; //꺼낼 때 visited
			cout << j << " "; 

			for (int i = graph[j].size() - 1; i >= 0; i--) {
				int next = graph[j][i];
				if (!visited[next]) {
					s.push(next);
				}
			}
		}
	}
}

void bfs(int start, const vector<vector<int>>& graph) {

	queue<int> q;
	vector<int> visited(graph.size() + 1);

	visited[start] = true;
	q.push(start);

	while (!q.empty()) {
		int j = q.front();
		q.pop();
		cout << j << " ";

		for (int i = 0; i < graph[j].size(); i++) {
			int next = graph[j][i];
			if (!visited[next]) {
				q.push(next);
				visited[next] = true; //넣을 때 visited
			}
		}
	}
}
