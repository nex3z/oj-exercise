#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_LENGTH = 1001;

void solveE6c_LongestOrderedSubsequence();

int main() {
    solveE6c_LongestOrderedSubsequence();
    return 0;
}

short seq[MAX_LENGTH], cnt[MAX_LENGTH];
void solveE6c_LongestOrderedSubsequence() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &seq[i]);
    }
    
    int result = 0;
    cnt[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int max = 0;
        for (int j = 1; j < i; ++j) {
            if (seq[j] < seq[i])
            max = max > cnt[j] ? max : cnt[j];
        }
        cnt[i] = max + 1;
        result = result > cnt[i] ? result : cnt[i];
    }
    
    printf("%d\n", result);
}