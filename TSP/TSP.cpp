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
