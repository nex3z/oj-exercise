#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 100 + 1;
const int MAX = 0x0fffffff;

void solveE7d_MultiplicationPuzzle();
int input(int num[]);

int main() {
	//freopen("test.txt", "r", stdin);
	solveE7d_MultiplicationPuzzle();
}

int num[MAX_N];
int f[MAX_N][MAX_N];
void solveE7d_MultiplicationPuzzle() {
	int n = input(num);

	for (int len = 1; len <= n - 2; ++len) {
		for (int start = 0; start + len + 1 < n; ++start) {
			int end = start + len + 1;
			if (len == 1) {
				f[start][end] = num[start]* num[start + 1] * num[end];
			} else {
				f[start][end] = MAX;
				for (int i = start + 1; i < end; ++i) {
					int cand = f[start][i] + f[i][end] + num[start] * num[i] * num[end];
					f[start][end] = f[start][end] < cand ? f[start][end] : cand;
				}
			}
		}
	}

	printf("%d\n", f[0][n - 1]);
}

int input(int num[]) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}
	return n;
}