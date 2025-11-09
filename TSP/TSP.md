# Traveling Salesperson Problem(TSP) (1)
![TSP](https://postfiles.pstatic.net/MjAyNTA1MTFfMjY0/MDAxNzQ2OTU2MDE0NzYy.iHR2O5qJWWcMSnhldFOu2d46IHyjvBQaDBaNRtuMvWMg.ykZAt78IyZGvuQGBoVWwD9a8SCbWhSNnZcnNxuBI1jMg.PNG/image.png?type=w773)<br>

## 1. 문제
한 외판원이 본사가 있는 도시에서 출발하여 모든 도시를 한 번 씩 순회하고 다시 본사가 있는 도시로 돌아오려고 한다. 
이 때 최소 일주 거리를 구하시오. 

## 2. 접근법
접근법은 브루트포스 방식과 다이나믹 프로그래밍 방식이 있으나 우선은 브루트포스로 접근하려고 한다.<br>
브루트포스 방식을 구현하기 위해 STL 함수인 `next_permutation()`을 사용하였다. `next_permutaion()`에 배열의 처음과 끝 포인터를 넣어주면
그 배열을 사전 순서대로 순열을 만들어준다. 가능한 모든 순열을 만들었을 때 false를 반환하므로, while문에 넣으면 브루트포스를 구현할 때 좋은
함수이다. 

## 3. 자료구조
(1) `int d[init][final]`: 도시 간의 거리를 저장하는 배열(예: d[0][1] = 1번 도시에서 2번 도시까지의 거리)<br>(*note: 인덱스 = 도시 번호 - 1*)<br>
(2) `vector<int> cities`: 도시 번호 배열. [0, n-1] 번호가 들어있다. <br>
(3) `bool valid`: 거리를 계산할 때 d[i][i+1]이 무한대라면 계산하지 않고 넘어가기 위한 플래그이다. <br>

## 4. 소스코드
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1e9
using namespace std;

int main() {
	int n = 4; //도시의 개수
	int d[10][10] = { {0,2,9,INF},
		{1,0,6,4},
		{INF,7,0,8},
		{6,3,INF,0} };
	int minCost = 1e9;

	vector<int> cities;
	for (int i = 0; i < n; i++) {
		cities.push_back(i);
	}

	do {
		int cost = 0;
		bool valid = true;
		for (int i = 0; i < n - 1; i++) {
			if (d[cities[i]][cities[i + 1]] == 1e9) {
				valid = false; break;
			}
			cost += d[cities[i]][cities[i + 1]];
		}

		if (valid && (d[cities[n - 1]][cities[0]] != 1e9))
		{
			cost += d[cities[n - 1]][cities[0]]; //본사로 돌아오는 거리
		    minCost = min(minCost, cost);
		}
	} while (next_permutation(cities.begin(), cities.end()));

	cout << minCost;
}
```
*출력: 21*
## 5. 고찰
- 마지막 if문에서 대괄호를 잘못 써서 에러가 났다. 다음에는 의미상 에러가 났을 때 대괄호를 꼼꼼히 확인해야겠다.
- n=5만 되어도 while루프를 5!=120번 수행해야한다. 따라서 위 접근법은 데이터의 양이 많을 때는 적절하지 않다. 
