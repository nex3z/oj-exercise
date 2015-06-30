#include <stdio.h>

#define MAX_N 1000
#define MAX_M 100000

void solveE2a();
void inputOrder(int m, int s[], int u[]);
void inputPlan(int n, int plan[]);
int verifyOrder(int m, int n, int s[], int u[], int plan[]);
void generateIndexLut(int n, int array[], int lut[]);
void printArray(int array[], int len);

int main(void) {
    solveE2a();
    return 0;
}


int s[MAX_M], u[MAX_M], plan[MAX_N];
void solveE2a() {
    int m, n, result;

    scanf("%d %d", &n, &m);
    inputOrder(m, s, u);
    inputPlan(n, plan);

    // printArray(s, m);
    // printArray(u, m);
    // printArray(plan, n);

    result = verifyOrder(m, n, s, u, plan);

    if (result) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

void inputOrder(int m, int s[], int u[]) {
    int i;

    for (i = 0; i < m; ++i) {
        scanf("%d %d", &s[i], &u[i]);
    }
}

void inputPlan(int n, int plan[]) {
    int i;

    for (i = 0; i < n; ++i) {
        scanf("%d", &plan[i]);
    }
}

int lut[MAX_N + 1];
int verifyOrder(int m, int n, int s[], int u[], int plan[]) {
    int i;

    generateIndexLut(n, plan, lut);
    // printArray(lut, n + 1);
    for (i = 0; i < m; ++i) {
        if (lut[s[i]] > lut[u[i]]) {
            return 0;
        }
    }
    return 1;
}

void generateIndexLut(int n, int array[], int lut[]) {
    int i;

    for (i = 0; i < n; ++i) {
        lut[array[i]] = i;
    }
}

void printArray(int array[], int len) {
    int i;

    for (i = 0; i < len; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}