#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 10000

void solveE5a_CableMaster();
double inputCables(int cables[], int n);
bool fit(int cables[], int n, double len, int targetNum);

int main() {
    solveE5a_CableMaster();
}

int cables[MAX_N];
void solveE5a_CableMaster() {
    int n, k;
    scanf("%d %d", &n, &k);

    double max = inputCables(cables, n);
    int l = 0, r = max, mid = (l + r) / 2;

    while (l <= r) {
        if (fit(cables, n, mid, k)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
        mid = (l + r) / 2;
    }

    printf("%.2f\n", mid * 0.01);
}

double inputCables(int cables[], int n) {
    int cm, m, max = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d.%d", &m, &cm);
        cables[i] = m * 100 + cm;
        max = cables[i] > max ? cables[i] : max;
    }
    return max;
}

bool fit(int cables[], int n, double len, int targetNum) {
    int num = 0;
    for (int i = 0; i < n; ++i) {
        num += cables[i] / len;
    }

    if (num >= targetNum)
        return true;
    else
        return false;
}