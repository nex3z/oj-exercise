#include <cstdio>

#define MAX_N 1500
#define IDX_NUM 0

typedef int Graph[MAX_N][11];
typedef int DP[MAX_N][2];

void solvePE8b_StrategicGame();
int input(Graph g, int n);
void dfs(int nodeIdAsRoot);
int min(int a, int b);

int main() {
	// freopen("test.txt", "r", stdin);
	solvePE8b_StrategicGame();
	return 0;
}

Graph graph;
DP dp;
void solvePE8b_StrategicGame() {
	int n;
	while (scanf("%d", &n) != -1) {
		int rootId = input(graph, n);

		dfs(rootId);

		int result = min(dp[rootId][0], dp[rootId][1]);
		printf("%d\n", result);
	}
}

void dfs(int nodeIdAsRoot) {
	int childNum = graph[nodeIdAsRoot][IDX_NUM];
	if (childNum == 0) {
		dp[nodeIdAsRoot][0] = 0;
		dp[nodeIdAsRoot][1] = 1;
		return;
	}
	else {
		dp[nodeIdAsRoot][0] = 0;
		dp[nodeIdAsRoot][1] = 0;
		for (int i = 1; i <= childNum; ++i) {
			int child = graph[nodeIdAsRoot][i];
			dfs(child);
			dp[nodeIdAsRoot][0] += dp[child][1];
			dp[nodeIdAsRoot][1] += min(dp[child][0], dp[child][1]);
		}
		++dp[nodeIdAsRoot][1];
	}
}

int min(int a, int b) {
	return a < b ? a : b;
}

bool isChild[MAX_N];
int input(Graph g, int n) {
	for (int i = 0; i < n; ++i) {
		isChild[i] = false;
	}

	for (int i = 0; i < n; ++i) {
		int id, num;
		scanf("%d:(%d)", &id, &num);
		g[id][IDX_NUM] = num;
		for (int j = 1; j <= num; ++j) {
			int leafId;
			scanf("%d", &leafId);
			g[id][j] = leafId;
			isChild[leafId] = true;
		}
	}

	for (int i = 0; i < n; ++i) {
		if (!isChild[i]) {
			return i;
		}
	}
	return -1;
}