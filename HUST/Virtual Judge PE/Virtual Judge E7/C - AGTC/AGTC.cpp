#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_LENGTH = 1000 + 10;

void solveE7c_AGTC();

int main() {
	solveE7c_AGTC();
	return 0;
}

char x[MAX_LENGTH], y[MAX_LENGTH];
int f[MAX_LENGTH][MAX_LENGTH];
void solveE7c_AGTC() {
	while (1) {
		int xLen, yLen;
		if (scanf("%d %s", &xLen, x) != 2)
			break;
		scanf("%d %s", &yLen, y);

		for (int i = 0; i < MAX_LENGTH; ++i) {
			f[i][0] = i;
			f[0][i] = i;
		}

		for (int i = 1; i <= xLen; ++i) {
			for (int j = 1; j <= yLen; ++j) {
				int cand1 = f[i - 1][j - 1],
					cand2 = f[i - 1][j] + 1,
					cand3 = f[i][j - 1] + 1;

				if (x[i - 1] != y[j - 1]) {
					++cand1;
				}
				f[i][j] = cand1 < cand2 ? cand1 : cand2;
				f[i][j] = f[i][j] < cand3 ? f[i][j] : cand3;
				// printf("%c %d %c %d %d\n", x[i - 1], i, y[j - 1], j, f[i][j]);
			}
		}

		printf("%d\n", f[xLen][yLen]);
	}

}
