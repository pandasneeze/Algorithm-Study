# 깊이 우선 탐색(DFS)
 깊이 우선 탐색(DFS)은 앞서 공부했던 넓이 우선 탐색(BFS)과 다르게 리프 노드까지 우선 탐색한 후 다른 노드로 넘어가는 방식이다. 
 트리에서 preorder 탐색이랑 비슷하다. 
 재귀함수로 구현하는 법과 스택으로 구현하는 법이 있는데 두 가지를 다 해보려고 한다. 

## 1. 문제
 ![DFS](https://postfiles.pstatic.net/MjAyNTA1MTJfNjQg/MDAxNzQ3MDIwNjQ5MTE3.lGN6vICUbNNgWgEe03lZtfmsumAcQJYJcOapA_otaLkg.e1Yy7NiFwJ1zjtha1twOT_g4cIeokzc_N7IeK75ESC4g.JPEG/SE-e2fcb634-ae1a-477b-8e58-55ee1d0826cd.jpg?type=w773)<br>
  예시 그래프는 BFS를 구현했을 때와 같은 트리를 사용했다. DFS를 했을 때 탐색 순서를 출력할 것이다. 

## 2. 접근법
(1) 시작 노드를 0으로 하고 스택에 삽입 후 방문 처리

(2) 스택의 최상단인 0과 인접한 노드 1, 2 중 가장 작은 노드인 1을 스택에 삽입 후 방문 처리 (현재 스택: 0,1)

(3) 스택의 최상단 = 1, min(1과 인접하고 방문하지 않은 노드인 3, 4) = 3이므로 3을 스택에 삽입 후 방문 처리(현재 스택: 0,1,3)

(4) 스택의 최상단 = 3인데 인접 노드 중 방문하지 않은 노드가 없으므로 스택에서 3을 pop (현재 스택: 0, 1)

(5) 스택의 최상단 = 1, 방문하지 않은 인접 노드 = 4이므로 4를 스택에 삽입 후 방문 처리

(6) 노드를 모두 방문하고 스택이 빌 때까지 반복

## 3. 자료구조
- STL 스택, 2차원 vector 사용

## 4. 소스코드
(1) 재귀호출
```cpp
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
```
(2) 스택
```cpp
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
```
## 5. 고찰
 - 재귀로 구현할 때는 push할 때 방문 처리를 하고 스택으로 구현할 때는 pop 할 때 방문 처리를 해야 한다. 

 - 스택으로 구현할 때 작은 노드를 먼저 탐색하게 하려면 for 루프를 내림차순으로 돌려야 한다. 스택은 LIFO이고 pop 할 때 visited 처리하기 때문이다. 

 - 재귀로 구현하는 것도 일종의 스택을 이용하는 것이다. 프로그램 실행 시 함수는 스택에 쌓이기 때문이다. 

​
