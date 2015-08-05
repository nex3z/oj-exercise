#include <stdio.h>
#include <string.h>

#define MAX_N 10005

void solveE2c();
void printArray(int array[], int len);

int main(void) {
    solveE2c();
    return 0;
}


int group[MAX_N + 1];
void solveE2c() {
    int n, k, m, tunnelCnt, groupCnt, groupIdCnt, src, dest, srcGroupId, destGroupId, i;

    memset(group, 0, sizeof(int) * (MAX_N + 1));
    scanf("%d %d %d", &n, &k, &m);

    tunnelCnt = k;
    groupCnt = 0;
    groupIdCnt = 0;
    while (tunnelCnt--) {
        scanf("%d %d", &src, &dest);
        srcGroupId = group[src];
        destGroupId = group[dest];
        if (srcGroupId != 0) {
            if (destGroupId != 0 && destGroupId != srcGroupId) {
                for (i = 1; i <= n; ++i) {
                    if (group[i] == destGroupId) {
                        group[i] = srcGroupId;
                    }
                }
                --groupCnt;
            } else {
                group[dest] = srcGroupId;
            }
        } else if (destGroupId != 0) {
            group[src] = destGroupId;
        } else {
            ++groupCnt;
            ++groupIdCnt;
            group[src] = groupIdCnt;
            group[dest] = groupIdCnt;
        }
        // printArray(group, n);
    }

    for (i = 1; i <= n; ++i) {
        if (group[i] == 0) {
            ++groupCnt;
        }
    }

    printf("%d\n", groupCnt - 1);
}


void printArray(int array[], int len) {
    int i;

    for (i = 1; i <= len; ++i) {
        printf("%d", array[i]);
    }
    printf("\n");
}