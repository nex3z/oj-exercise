#include <cstdio>

#define MAX_N 101
#define MAX_TIME 10000

typedef int Cost[MAX_N][MAX_N];

void solvePE8a_StockbrokerGrapevine();
int input(Cost c);
void floyd(Cost c, int n);

int main() {
	// freopen("test.txt", "r", stdin);
	solvePE8a_StockbrokerGrapevine();
	return 0;
}

Cost cost;
void solvePE8a_StockbrokerGrapevine() {
	while (1) {
		int n = input(cost);
		if (n == 0) {
			return;
		}
		floyd(cost, n);
	
		int min = MAX_TIME, select = 0, disjoint = false;
		for (int i = 1; i <= n; ++i) {
			int cand = 0;
			disjoint = false;
			for (int j = 1; j <= n; ++j) {
				if (i != j) {
					if (cost[i][j] == MAX_TIME) {
						disjoint = true;
						break;
					}
					cand = cand > cost[i][j] ? cand : cost[i][j];
				}
			}
			if (!disjoint && min > cand) {
			min = cand;
			select = i;
			}
		}
		if (min == MAX_TIME) {
			printf("disjoint\n");
		} else {
			printf("%d %d\n", select, min);
		}
	}
}

int input(Cost c) {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			c[i][j] = MAX_TIME;
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		int contactNum;
		scanf("%d", &contactNum);
		for (int j = 1; j <= contactNum; ++j) {
			int contact, time;
			scanf("%d %d", &contact, &time);
			c[i][contact] = time;
		}
	}
	
	return n;
}

void floyd(Cost c, int n) {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				int cand = c[i][k] + c[k][j];
				c[i][j] = c[i][j] < cand ? c[i][j] : cand;
			}
		}
	}
}