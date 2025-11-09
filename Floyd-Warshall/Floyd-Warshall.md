# Floyd-Warshall 알고리즘
## 1. 문제
![문제](https://postfiles.pstatic.net/MjAyNTA1MDhfMyAg/MDAxNzQ2NzA0NTU2MjA1.CnO6nMWQyIhlCbnVFVg89VIYgLw20-yFfLwt8f4uQFog.zMLGhl7pd4D7_lj5PkGZoKb_7lP2ChwmyCrawY_EeUMg.PNG/image.png?type=w773)
<br>가중치 포함 그래프의 각 정점에서 다른 모든 정점까지의 최단 거리를 계산하라.
- 입력: 가중치 포함, 방향성 그래프 W와 그 그래프에서의 정점의 수 n
- 출력: 최단 거리의 길이가 포함된 배열 D

## 2. 접근법
(1) brute force: 한 정점에서 다른 정점으로의 모든 경로의 경우의 수를 나열한 뒤, 경로의 길이를 계산<br>
(2) Floyd-Warshall 알고리즘: 모든 정점 간의 거리를 저장한 뒤, 거쳐가는 점이 있을 때와 없을 때의 거리를 비교하여 더 짧은 거리를 대입하는 방법<br>
  점화식: $D_ab = min(D_ab, D_ak + D_kb)$<br>

## 3. 자료구조
(1) W[init][final]: 정점 간 거리 (예: W[1][4] = 1, $v_1$ --> $v_4$ 거리가 1이므로)<br>
출발/도착|v1|v2|v3|v4|v5
---|---|---|---|---|---
v1|0|1|∞|1|5
v2|9|0|3|2|∞
v3|∞|∞|0|4|∞
v4|∞|∞|2|0|3
v5|3|∞|∞|∞|0
<br>
(2) D[init][final]: 최단 거리<br>
(3) P[init][final]: init부터 final까지 최단 경로에서 거쳐가는 정점 중 가장 인덱스가 큰 정점(없는 경우 0)<br>

## 4. 소스코드
```cpp
#define N 6
void Floyd(int W[][N], int D[][N], int P[][N]) {
	//P = 0으로 초기화
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			P[i][j] = 0;
	//D = W
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			D[i][j] = W[i][j];

	//D, P 구함
	for (int k = 1; k < N; k++) { //k는 거쳐가는 점
		for (int i = 1; i < N; i++) { //i = init
			for (int j = 1; j < N; j++) { //j = final
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
			}
		}
	}
}
```

## 5. 고찰
- 인덱스와 정점의 번호를 일치시키기 위해 배열의 크기를 정점의 갯수보다 1만큼 더 크게 설정하였다.
- 처음에 코드를 작성할 때 `D[i][j] = D[i][k] + D[k][j]`를 `D[i][j] = W[i][k] + W[k][j]`로 잘못 작성하였다. 
그 결과로 D 배열에 자꾸 무한대 값이 대입되었다.
Floyd-Warshall 알고리즘은 이전의 계산 결과를 저장하여 다음에 활용하는 다이나믹 프로그래밍 방식이므로, 
W 배열을 사용하면 값이 업데이트 되지 않으므로 오류가 발생한다. 
- P 배열을 이용하여 최단 루트를 구할 수 있다. P[init][final] 값을 P = 0일 때까지 참조한 후, 
P = 0을 만나기 직전 P(이 때 P는 중간에 거쳐가는 점을 의미하게 된다)를 출력하고 다시 한 번 P[거쳐가는점][final]을 재귀적으로 참조하면 
최단루트를 알 수 있다.
```cpp
void path(int P[][N], int init, int final) {
	if (P[init][final] != 0) {
		path(P, init, P[init][final]);
		cout << "v" << P[init][final] << " ";
		path(P, P[init][final], final);
	}
}
```
