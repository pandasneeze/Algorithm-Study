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
