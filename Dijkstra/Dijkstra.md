# 다익스트라(Dijkstra) 알고리즘
 다익스트라(Dijkstra) 알고리즘은 최단 경로 찾기 알고리즘입니다. 
 이전에 다뤘던 Floyd-Warshall과는 한 정점에 대하여 다수 정점의 최단 경로를 찾는 다는 점이 다릅니다(Floyd-Warshall은 다수:다수). 
 아래 표는 둘을 비교한 것입니다. <br>
 
 | |시간복잡도|음의 가중치|특징|
|---|---|---|---|
|다익스트라|$O((n+m)log n)$ (우선순위 큐 사용시)<br>$O(n^2)$|불가능|- dense한 그래프<br> - 인접 행렬|
|Floyd-Warshall|$O(n^3)$|가능|- dense한 그래프<br> - 인접 행렬|
<br>

아래 블로그를 참고했으니 동작 설명은 아래를 봐주세요
[[다익스트라 알고리즘] 개념과 구현방법(C++)](https://yabmoons.tistory.com/364)
<br>

## 소스코드
```cpp
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
```
## 설명
 - `graph[][]`: graph를 표현하는 자료구조로, 인접 행렬을 사용했습니다. 이번에는 노드가 1부터 시작할 거라고 가정해서 인덱스 번호와 노드 번호를 일치시켰습니다. 

​

 - `Dijkstra(start, end, graph)`: 다익스트라 알고리즘이 1:다수임에도 도착 정점을 받게 한 이유는 경로를 출력하기 위해서였습니다. stack 배열을 사용하면 모든 경로를 한꺼번에 출력할 수 있습니다.

​

 - `visited[]`: 노드의 방문 여부를 저장하는 배열입니다. 처음엔 모두 false로 초기화 했습니다.

​

 - `dist[]`: 출발 노드에서 도착 노드까지 최단 거리를 저장하는 배열입니다. dist[5]라면 start 노드에서 5번 노드까지의 최단 거리입니다.

​

 - `prev[]`: 경로를 추적하기 위한 배열입니다. 해당 노드로 가기 위해 마지막으로 거쳐간 노드가 저장됩니다. 거쳐가는 노드가 없다면 -1이 저장됩니다. 예를 들어 prev[4] = x이고 prev[x] = -1라면 1번노드에서 4번 노드의 경로는

[1 -> x -> 4]가 됩니다. 이를 스택에 저장하고 pop하면 출발 -> 도착 순서로 출력할 수 있습니다.

​

 - **요약**: 거리가 가장 가깝고 방문하지 않은 노드를 찾고, 그 노드를 거치는 경우가 거치지 않는 경우보다 거리가 짧다면 dist를 업데이트 합니다. 이 때 이미 방문한 노드는 고려하지 않습니다.(때문에 다익스트라 알고리즘에서 음의 가중치가 들어간다면 정확한 해를 구할 수 없게 됩니다.)

## 고찰
- 우선순위 큐로 구현한다면 실행시간을 더욱 빠르게 개선할 수 있습니다.
- 아래는 손코딩 했던 것 입니다.
![사진](https://postfiles.pstatic.net/MjAyNTA1MjVfMTIz/MDAxNzQ4MTc1NDIwNzkz.qaFFqEer-aeQNcS8ACoSNA4PHkGJPNSbl6fjTgvRUWEg.Dh6ivR77bIUakexipjiIXG9BwfZ1If9MWhL2G8yqEZwg.JPEG/IMG_2662.jpeg?type=w773)
