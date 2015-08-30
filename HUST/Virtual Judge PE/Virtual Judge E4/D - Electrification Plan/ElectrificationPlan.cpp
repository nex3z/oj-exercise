#include <stdio.h>

#define MAX_CITY_NUM 101
#define MAX_COST 100001

typedef int CostMap[MAX_CITY_NUM][MAX_CITY_NUM];

void solveE3d_ElectrificationPlan();
void inputCostMap(CostMap costMap, int n);

int main() {
    solveE3d_ElectrificationPlan();
    return 0;
}

int powerStations[MAX_CITY_NUM];
CostMap costMap;
bool hasPower[MAX_CITY_NUM];
void solveE3d_ElectrificationPlan() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; ++i) {
        scanf("%d", &powerStations[i]);
        hasPower[powerStations[i]] = true;
    }

    inputCostMap(costMap, n);

    int minCost = MAX_COST, minCostId, totalCost = 0;
    while (k < n) {
        minCost = MAX_COST;
        for (int i = 1; i <= n; ++i) {
            if (!hasPower[i]) {
                for (int j = 0; j < k; ++j) {
                    if (costMap[i][powerStations[j]] < minCost) {
                        minCost = costMap[i][powerStations[j]];
                        minCostId = i;
                    }
                }
            }
        }
        totalCost += minCost;
        hasPower[minCostId] = true;
        powerStations[k++] = minCostId;
    }

    printf("%d\n", totalCost);
}

void inputCostMap(CostMap costMap, int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &costMap[i][j]);
        }
    }
}