#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAD_NUM 20001

void solveE4e_DragonOfLoowater(int headNum, int knightNum);
int cmp(const void *a, const void *b);

int main() {
    int headNum, knightNum;
    
    scanf("%d %d", &headNum, &knightNum);
    while (headNum != 0 || knightNum != 0) {
        solveE4e_DragonOfLoowater(headNum, knightNum);
        scanf("%d %d", &headNum, &knightNum);
    }

    return 0;
}

int heads[MAX_HEAD_NUM], knights[MAX_HEAD_NUM];
void solveE4e_DragonOfLoowater(int headNum, int knightNum) {
    for (int i = 0; i < headNum; ++i) {
        scanf("%d", &heads[i]);
    }
    
    for (int i = 0; i < knightNum; ++i) {
        scanf("%d", &knights[i]);
    }
    
    qsort(heads, headNum, sizeof(int), cmp);
    qsort(knights, knightNum, sizeof(int), cmp);
    
    int i, j = 0, cost = 0;
    bool killed = false;
    for (i = 0; i < headNum; ++i) {
        killed = false;
        for (; j < knightNum; ++j) {
            if (heads[i] <= knights[j]) {
                cost += knights[j];
                killed = true;
                ++j;
                break;
            }
        }
        if (!killed) {
            printf("Loowater is doomed!\n");
            return;
        }
    }
    
    printf("%d\n", cost);
}

int cmp(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}