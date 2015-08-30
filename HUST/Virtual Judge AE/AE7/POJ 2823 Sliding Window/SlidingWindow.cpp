#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 1000000

void solveAE7a_SlidingWindow();

int main() {
    solveAE7a_SlidingWindow();
    return 0;
}

int num[MAX_N], maxIdxQueue[MAX_N], minIdxQueue[MAX_N], maxAnswer[MAX_N];
void solveAE7a_SlidingWindow() {
    int n, k;
    scanf("%d %d", &n, &k);
    if (n == 0 || k == 0)
        return;

    int maxHead = 0, maxTail = 0, minHead = 0, minTail = 0;
    scanf("%d", &num[0]);
    maxIdxQueue[maxTail++] = 0;
    minIdxQueue[minTail++] = 0;
    if (k == 1)
        printf("%d ", num[minIdxQueue[minHead]]);

    for (int i = 1; i < n; ++i) {
        scanf("%d", &num[i]);

        while (maxTail > maxHead && num[i] > num[maxIdxQueue[maxTail - 1]])
            --maxTail;
        maxIdxQueue[maxTail++] = i;
        if (i >= maxIdxQueue[maxHead] + k)
            ++maxHead;

        while (minTail > minHead && num[i] < num[minIdxQueue[minTail - 1]])
            --minTail;
        minIdxQueue[minTail++] = i;
        if (i >= minIdxQueue[minHead] + k)
            ++minHead;

        if (i >= k - 1) {
            printf("%d ", num[minIdxQueue[minHead]]);
            // printf("%d ", num[maxIdxQueue[maxHead]]);
            maxAnswer[i] = maxIdxQueue[maxHead];
        }
    }
    printf("\n");
    for (int i = k - 1; i < n; ++i) {
        printf("%d ", num[maxAnswer[i]]);
    }
    printf("\n");
}