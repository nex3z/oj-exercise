#include <stdio.h>

#define MAX_N 10001
#define MAX_M 10001

void solveE1A();

int main() {
    solveE1A();
    return 0;
}

int votes[MAX_M] = {0};
void solveE1A() {
    int candNum, electorNum, cand, i;
    float percent;
    
    scanf("%d %d", &candNum, &electorNum);
    
    for (i = 1; i <= electorNum; ++i) {
        scanf("%d", &cand);
        ++votes[cand];
    }
    
    for (i = 1; i <= candNum; ++i) {
        percent = 100.0 * votes[i] / electorNum;
        printf("%2.2f%%\n", percent);
    }
}
