#include <iostream>
#include <vector>
#include <stack>
#define INF 10000
using namespace std;

void Dijkstra(int start, int end, const vector<vector<int>>& graph);
int main() {
	const vector<vector<int>>graph = {
		{0},
		{0,0,4,2,INF,INF,INF},
		{0,4,0,INF,4,5,INF},
		{0,2,INF,0,INF,4,INF},
		{0,INF,4,INF,0,INF,1},
		{0,INF,5,4,INF,0,2},
		{0,INF,INF,INF,1,2,0}
	};

	Dijkstra(1, 4, graph);
}

void Dijkstra(int start, int end, const vector<vector<int>>& graph) {

	//visited 배열 초기화

	vector<bool> visited(graph[start].size(), false);
	visited[start] = true;

	
	//dist 배열 초기화

	vector<int> dist;
	for (int i = 0; i < graph[start].size(); i++) {
		dist.push_back(graph[start][i]);
	}

	//경로 저장 배열
	vector<int> prev(dist.size(), -1);

	//dijkstra

	for (int i = 1; i < graph[start].size(); i++) {

		//거리가 가장 가깝고 방문하지 않은 노드 찾기

		int u = -1; //가장 가까운 노드
		int minWeight = INF;

		for (int i = 1; i < graph[start].size(); i++) {
			if (!visited[i] && (dist[i] < minWeight)) {
				u = i;
				minWeight = dist[i];
			}
		}


		//거리 업데이트

		if (u == -1) continue;

		visited[u] = true;

		for (int i = 1; i < graph[start].size(); i++) {
			if (!visited[i] && (dist[i] > dist[u] + graph[u][i])) {
				dist[i] = dist[u] + graph[u][i];
				prev[i] = u;
			}//if
		}//for
	}//for

	//결과 출력
	std::cout << "1  2  3  4  5  6" << endl;
	std::cout << "-----------------" << endl;
	for (int i = 1; i < dist.size(); i++) {
		std::cout << dist[i] << "  ";
	}
	std::cout << endl << endl;

	//경로
	stack<int> path;
	for (int i = end; i != -1; i = prev[i]) {
		path.push(i);
	}

	std::cout << start << " -> ";
	while (!path.empty()) {
		std::cout << path.top();
		path.pop();
		if (!path.empty()) std::cout << " -> ";
	}
	std::cout << endl << endl;
}
