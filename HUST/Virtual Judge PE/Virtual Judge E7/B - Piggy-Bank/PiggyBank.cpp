#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 10000 + 1;
const int MAX_WEIGHT = 0x0fffffff;

void solveE7a_PiggyBank();
void input(int p[], int w[], int n);

int main() {
	int tcNum;
	scanf("%d", &tcNum);

	while (tcNum--) {
		solveE7a_PiggyBank();
	}
}

int p[MAX_N], w[MAX_N], f[MAX_N];
void solveE7a_PiggyBank() {
	int empty, full;
	scanf("%d %d", &empty, &full);
	int weight = full - empty;

	int n;
	scanf("%d", &n);
	input(p, w, n);

	for (int i = 1; i < MAX_N; ++i) {
		f[i] = MAX_WEIGHT;
	}
	f[0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int v = w[i]; v <= weight; ++v) {
			int cand = f[v - w[i]] + p[i];
			f[v] = cand < f[v] ? cand : f[v];
		}
	}

	if (f[weight] != MAX_WEIGHT) {
		printf("The minimum amount of money in the piggy-bank is %d.\n", f[weight]);
	}
	else {
		printf("This is impossible.\n");
	}
}

void input(int p[], int w[], int n) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &p[i], &w[i]);
	}
}