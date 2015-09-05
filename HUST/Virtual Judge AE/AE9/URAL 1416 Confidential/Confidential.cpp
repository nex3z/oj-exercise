#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 501
#define MAX_W 1001

typedef short Cost[MAX_N][MAX_N];

void solveE9b_Confidential();
void inputCost(Cost cost, int n, int passageNum);
void init(Cost cost, int n, int value);

int main() {
    solveE9b_Confidential();
}

Cost cost, cand;
int connectedNum;
// unsigned char connected[MAX_N];
short connected[MAX_N];
bool isConnected[MAX_N];
void solveE9b_Confidential() {
    int n, m;
    scanf("%d %d", &n, &m);

    inputCost(cost, n, m);

    init(cand, n, 0);
    connected[connectedNum++] = 1;
    isConnected[1] = true;

    int totalCost = 0;
    while (connectedNum < n) {
        int minCost = MAX_W, minCostId, minCostConnectedId;
        for (int i = 1; i <= n; ++i) {
            if (!isConnected[i]) {
                for (int j = 0; j < connectedNum; ++j) {
                    if (cost[i][connected[j]] < minCost) {
                        minCost = cost[i][connected[j]];
                        minCostId = i;
                        minCostConnectedId = connected[j];
                    }
                }
            }
        }

        for (int i = 0; i < connectedNum; ++i) {
            cand[connected[i]][minCostId] = cand[connected[i]][minCostConnectedId] > minCost ? cand[connected[i]][minCostConnectedId] : minCost;
            cand[minCostId][connected[i]] = cand[connected[i]][minCostId];
        }
        
        totalCost += minCost;
        connected[connectedNum++] = minCostId;
        isConnected[minCostId] = true;
        cost[minCostId][minCostConnectedId] = MAX_W;
        cost[minCostConnectedId][minCostId] = MAX_W;
    }

    int extraCost, minExtraCost = MAX_W;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((i != j) && (cost[i][j] < MAX_W)) {
                extraCost = cost[i][j] - cand[i][j];
                if (extraCost < minExtraCost) {
                    minExtraCost = extraCost;
                }
            }
        }
    }
    int newTotalCost = minExtraCost == MAX_W ? -1 : (totalCost + minExtraCost);

    printf("Cost: %d\n", totalCost);
    printf("Cost: %d\n", newTotalCost);
}

void inputCost(Cost cost, int n, int passageNum) {
    init(cost, n, MAX_W);

    int a, b, w;
    for (int i = 0; i < passageNum; ++i) {
        scanf("%d %d %d", &a, &b, &w);
        cost[a][b] = w;
        cost[b][a] = w;
    }
}

void init(Cost cost, int n, int value) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cost[i][j] = value;
        }
    }
}