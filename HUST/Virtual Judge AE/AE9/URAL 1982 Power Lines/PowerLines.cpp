#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 101
#define MAX_COST 100001

typedef int Cost[MAX_N][MAX_N];

void solveE7A_PowerLines();
void inputCost(Cost cost, int n);

int main() {
	solveE7A_PowerLines();
}

unsigned char poweredCityId[MAX_N];
bool isPowered[MAX_N];
Cost cost;
void solveE7A_PowerLines() {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= k; ++i) {
		scanf("%d ", &poweredCityId[i]);
		isPowered[poweredCityId[i]] = true;
	}

	inputCost(cost, n);

	int totalCost = 0;
	while (k < n) {
		int minCost = MAX_COST, minCostId = 0;
		for (int j = 1; j <= n; ++j) {
			if (!isPowered[j]) {
				for (int l = 1; l <= k; ++l) {
					if (cost[j][poweredCityId[l]] < minCost) {
						minCost = cost[j][poweredCityId[l]];
						minCostId = j;
					}
				}
			}
		}
		totalCost += minCost;
		poweredCityId[++k] = minCostId;
		isPowered[minCostId] = true;
	}

	printf("%d\n", totalCost);
}	

void inputCost(Cost cost, int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &cost[i][j]);
		}
	}
}