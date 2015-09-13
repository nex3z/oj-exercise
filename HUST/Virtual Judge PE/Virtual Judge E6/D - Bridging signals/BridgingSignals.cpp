#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 40001;

void solveE6d_BridgingSignals();
int binarySearch(int array[], int len, int target);

int main() {
    int tcNum;
    scanf("%d", &tcNum);
    
    while (tcNum--)
    solveE6d_BridgingSignals();
}

int signal[MAX_N], lastId[MAX_N];
void solveE6d_BridgingSignals() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i)
    scanf("%d", &signal[i]);
    
    for (int i = 1; i <= n; ++i)
    lastId[i] = MAX_N;
    
    int currLen = 1;
    lastId[currLen] = signal[1];
    for (int i = 2; i <= n; ++i) {
        if (signal[i] > lastId[currLen]) {
            lastId[++currLen] = signal[i];
        } else {
            int pos = binarySearch(lastId, currLen, signal[i]);
            lastId[pos] = signal[i];
        }
    }
    
    printf("%d\n", currLen);
}

int binarySearch(int array[], int len, int target) {
    int l = 1, r = len, mid;
    while (l <= r) {
        mid = (r + l) / 2;
        if (target < array[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}