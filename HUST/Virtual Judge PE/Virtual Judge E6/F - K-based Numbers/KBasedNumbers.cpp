#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 19;

void solveE6f_KBasedNumbers();

int main() {
    solveE6f_KBasedNumbers();
}

int cnt[MAX_N][2];
void solveE6f_KBasedNumbers() {
    int n, k;
    scanf("%d%d", &n, &k);
    
    cnt[1][0] = 0;
    cnt[1][1] = k - 1;
    for (int i = 2; i <= n; ++i) {
        cnt[i][0] = cnt[i - 1][1];
        cnt[i][1] = (cnt[i - 1][1] + cnt[i - 1][0]) * (k - 1);
    }
    
    printf("%d\n", cnt[n][0] + cnt[n][1]);
}