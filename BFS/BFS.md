# 너비 우선 탐색(BFS)
 그래프 탐색 방법에는 너비 우선 탐색(Breadth-First Search, BFS)와 깊이 우선 탐색(Depth-First Search, DFS)이 있는데, 이번에는 BFS로 간단한 그래프를 탐색해 보려 한다. 

 ## 1. 문제
 ![BFS](https://postfiles.pstatic.net/MjAyNTA1MTFfMjcw/MDAxNzQ2OTczMzY2Nzcz.g_ZNJdbBnbTHBYLzyHDad9UNBqHjzyqu9DpD9wz_Mfgg.-YTAf_Dc7T-JkccMh2zruTli6741MwAFENCAd5LuFnsg.JPEG/SE-c557943e-8fbd-4f38-98c3-914a5b668d40.jpg?type=w773)<br>
 연습을 위해 예시 트리를 그려보았다. 위의 트리를 BFS 했을 때 탐색 순서를 출력하려고 한다.

 ## 2. 접근법
 BFS는 시작 노드에서 인접한 노드를 먼저 탐색하는 방법이다. 예를 들어 시작 노드를 0이라고 하면

(1) 0을 방문 처리 후 큐에 0 저장

(2) 큐에서 0을 pop

(3) 0과 인접한 노드가 1, 2이므로 큐에 1, 2 저장 -> 노드 1, 2 방문 처리 (현재 큐: 1,2)

(4) 큐에서 1을 pop

(5) 1과 인접한 노드는 3이므로 큐에 3 저장 -> 노드 3 방문 처리 (현재 큐: 2,3)

(6) 큐에서 2를 pop -> 2의 인접 노드 큐에 저장 -> 방문 처리 -> 큐를 pop -> 큐가 빌 때까지 반복

(7) 출력: 0 1 2 3 4 5<br>

## 3. 자료구조
(1) `vector<vector<int>> graph`: 2차원 벡터이다. 예시 그래프는 가중치가 없는 양방향 그래프(트리)이기 때문에 인접 행렬 방식으로 해도 되지만, 
인접 리스트 방식이 활용도가 높을 것 같아 해당 방식으로 연습해 보았다. 
```cpp
const vector<vector<int>> graph = {
	{1,2},
	{0,3,4},
	{0,5},
	{1},
	{1},
	{2}
};
```
(2) `vector<bool> visited`: 노드의 방문 여부를 저장하는 배열이다. 모두 false로 초기화되어있다.<br>
(3) `queue<int> q`: BFS 방식으로 탐색을 할 수 있게 해주는 자료구조이다. BFS는 DFS와 다르게 큐를 사용한다.<br>
![인접리스트](https://postfiles.pstatic.net/MjAyNTA1MTFfMTE4/MDAxNzQ2OTc1MjQyMzg0.64JZ_AT7VpYuJDqzAt_0Lvm9zd44DyRNZz5CjmbVt-Ig.pl30pmA53DfwqdG1IYiUfo1pLF5BCbGCA4_VDzqW4z0g.JPEG/IMG_2656.jpeg?type=w773)<br>

## 4. 소스코드
```cpp
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
```
*출력: 0 1 2 3 4 5*<br>
## 5. 고찰
- 위 예시 그래프는 가중치가 없는 양방향 그래프(트리)이므로 graph의 자료형을 2차원 배열로 설정해도 된다.
 아래 사진은 인접 행렬 방식의 그래프일 때 직접 손 코딩해 본 것이다.<br>
 ![인접 행렬](https://postfiles.pstatic.net/MjAyNTA1MTFfNDkg/MDAxNzQ2OTc0NjU0NjUx.0EsR_jpjBJgVWeG-YjuaedTEnNegPoOEJRcD4oBXxzkg.vJjswK8i2v5UNp9K7YAhBaTKTWilg90hyjp3zaTeb7kg.JPEG/IMG_2655.jpeg?type=w773)<br>
 ```cpp
void bfs(int start) {
	int n = 6;
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

		for (int i = 0; i < n; i++) {
			if(graph[x][i]&&(!visited[i])){
				visited[i] = true;
				q.push(i);
			}
		}
	}
}
```
  

