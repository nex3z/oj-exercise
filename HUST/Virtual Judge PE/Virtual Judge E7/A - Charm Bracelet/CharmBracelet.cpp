#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 3402 + 1;
const int MAX_W = 12880 + 1;

void solveE7a_CharmBracelet();
void input(int w[], int d[], int n);

int main() {
	solveE7a_CharmBracelet();
}

int f[MAX_W], w[MAX_N], d[MAX_N];
void solveE7a_CharmBracelet() {
	int n, m;
	scanf("%d %d", &n, &m);
	input(w, d, n);

	for (int i = 1; i <= n; ++i) {
		for (int j = m; j >= w[i]; --j) {
			f[j] = (f[j - w[i]] + d[i]) > f[j] ? (f[j - w[i]] + d[i]) : f[j];
		}
	}

	printf("%d\n", f[m]);
}

void input(int w[], int d[], int n) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &w[i], &d[i]);
	}
}