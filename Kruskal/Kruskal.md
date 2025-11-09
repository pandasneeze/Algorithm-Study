# Kruskal 알고리즘
 Kruskal 알고리즘은 최소 비용 신장 트리를 만들어주는 알고리즘이다. 
 여기서 신장 트리(spanning tree)란, 간선을 노드의 개수보다 하나 적은 수만큼 남겨 놓은 트리이다. 
 원래의 그래프가 한 노드에서 다른 노드로 가는 경로가 두 개 이상 존재했다면, 신장 트리는 경로 하나만 남겨 놓고 나머지 경로를 제거한 트리라고 볼 수 있다. 
![자료](https://postfiles.pstatic.net/MjAyNTA1MjFfMjM5/MDAxNzQ3ODIyMDEwOTg4.m6j_82FWtsGwsaz3YuxmhQAhYI05mtZRLy6Y7fVOrwwg.0R3nhpl_6q7HOtSiTzDvG_Hca_D-SlfwlgLXAI43y2gg.PNG/image.png?type=w773)<br>
※신장 트리의 제한 조건

 - 가중치가 부여된 무방향 그래프

 - n - 1개의 간선만 사용

 - **사이클**을 생성하면 안 됨<br>
#### 사이클
아래 그림처럼 갈 수 있는 길이 여러 가지이면 사이클이 생긴다. <br>
![cycle](https://postfiles.pstatic.net/MjAyNTA1MjFfMTIx/MDAxNzQ3ODIzMjU5NDQ4.hk9PvFLSbXGkVLh9-4dozU5azpViBsMRCY6n4e3ujgEg.PMQLRjBiIvwVCVSM_ABeL1B5R3oa5eDHHohnoxWMc80g.JPEG/SE-797c9856-d428-48c6-b5ba-386070662607.jpg?type=w773)<br>
사이클 생성 여부를 판단하려면 union-find 알고리즘을 사용하면 된다. union-find는 노드가 같은 그룹인지, 다른 그룹인지 판별해 주는 알고리즘이다. 
Kruskal로 생각하면 서로 오갈 수 있다면 같은 그룹이고, 떨어져 있다면 다른 그룹이다. 
간선을 선택할 때 union-find로 같은 그룹이라고 판단되면 해당 간선은 버려야 한다. 
(*note: 같은 그룹이다 --> 이미 두 노드를 잇는 간선이 존재한다. 따라서 여기서 간선을 더 선택하면 사이클을 형성하게 되므로 해당 간선은 버려야 한다.*)

#### Union-find 알고리즘
Union-find는 초기화(makeSet) -> 합치기(union) -> 찾기(find)의 3단계 과정을 거친다.<br>
이 알고리즘은 트리 구조를 이용하는데, A 노드와 B 노드가 같은 집합이면, 같은 부모를 갖게 함으로써 같은 그룹인지 아닌지를 판단한다. 

(1) 초기화(makeSet)

 노드의 수만큼 parent 배열을 만들고 배열에 자기 자신의 노드 번호를 대입한다. 이 배열은 노드의 부모를 의미한다.

​

(2) 합치기(union)

 예를 들어 union(1, 2)를 호출하면 1번 노드와 2번 노드를 같은 그룹에 넣는다는 의미이다. 이때 인덱스가 작은(또는 큰) 노드를 대표 노드로 설정하여 작은 노드를 부모 노드로 한다. 즉, union(1, 2)를 호출하면 2번 노드의 부모를 1로 바꾼다. 아래는 의사코드이다.
```cpp
if (노드1 != 노드2)  //중복을 피하기 위한 조건
    if (노드1 < 노드2)  //작은 노드를 대표 노드로 하기 위해 크기 비교
        parent[노드2] = 노드1 //큰 노드가 작은 노드의 자식으로
```
(3) 찾기(find)

 find는 트리의 최상위 노드(그룹의 대표 노드)를 반환한다. 최상위를 찾아야 하기 때문에 재귀 호출이 들어간다. 
 만약 두 노드의 find 리턴 값이 같다면 두 노드는 같은 그룹인 것이다. 아래는 의사코드이다. 
```cpp
int find(노드) {
    if ( parent[노드] != 노드 ) //자신의 부모가 자기 자신이 아니라면 -> 상위 노드가 존재
        parent[노드] = find(parent[노드]) //최상위 노드 찾기
    else return 노드 //자신의 부모가 자기 자신 -> 그룹의 대표 노드
    return parent[노드] //상위 노드
```
(4) Union-find 알고리즘 전체 소스코드
```cpp
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
```
### Kruskal 알고리즘
다시 Kruskal 알고리즘으로 돌아와서 동작을 살펴보면

(1) 노드 u, v와 두 노드를 잇는 간선의 가중치를 가지고 있는 struct 배열 Edge

(2) 가중치에 대해 오름차순으로 Edge 배열을 정렬

(3) 가중치가 작은 순서대로 탐색 시작

(4) 간선을 선택했을 때 그래프가 사이클을 형성하면 간선을 버리고, 그렇지 않으면 선택

- 자료구조
```cpp
struct Edge {
	int u, v, weight; //노드 u, v, 가중치
	bool operator<(const Edge& other) const { //sort에서 사용할 연산자 < 오버로딩
		return weight < other.weight; //가중치에 대해 오름차순 정렬
	}
};
```
위 struct를 간선의 수만큼 배열을 만들어서 사용하면 된다. <br>
- 소스코드
```cpp
void kruskal(int n, vector<Edge>& edges) {
	makeSet(n);
	sort(edges.begin(), edges.end()); //weight에 대해 sort

	for (Edge e : edges) { //작은 간선부터 순서대로
		if (find(e.u) != find(e.v)) { //같은 그룹이 아니면
			unionSets(e.u, e.v); //간선 선택
		}
	}
}
```

## 고찰
 Kruskal 알고리즘은 그리디(greedy) 알고리즘이다. 
 그리디 알고리즘은 순간마다 최적의 선택을 하는 방법이다. 
 따라서 그 순간에서는 최적의 선택일 지 몰라도 전체로 봤을 때 최적의 해가 아닐 가능성이 있다. 
 하지만 Kruskal 알고리즘은 최적의 해임이 증명되었다고 한다. (아마 최소 신장 트리 문제이기에 가능한 것 같다. 여러 간선이 있을 때 가중치가 작은 간선부터 확정하고 최소의 개수만 남기는 것이다 보니)
