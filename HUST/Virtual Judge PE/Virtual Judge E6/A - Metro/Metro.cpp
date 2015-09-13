#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_N 1001
#define SQRT_2 1.4142135623730950488016887242097

typedef bool CanCross[MAX_N][MAX_N];

void solveE6a_Metro();
int input(CanCross canCross, int rowNum, int colNum);
double min(double a, double b, double c);

int main() {
    solveE6a_Metro();
}

double dist[MAX_N][MAX_N];
CanCross canCross;
void solveE6a_Metro() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    input(canCross, m, n);
    
    for (int i = 0; i <= m; ++i)
    dist[i][0] = i;
    
    for (int i = 0; i <= n; ++i)
    dist[0][i] = i;
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = min(dist[i - 1][j] + 1,
                             dist[i][j - 1] + 1,
                             dist[i - 1][j - 1] + (canCross[i][j] ? SQRT_2 : 2));
        }
    }
    int result = dist[m][n] * 100 + 0.5;
    printf("%d\n", result);
}

int input(CanCross canCross, int rowNum, int colNum) {
    int k;
    scanf("%d", &k);
    
    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        canCross[y][x] = true;
    }
    
    return k;
}

double min(double a, double b, double c) {
    double tmp = a < b ? a : b;
    return tmp < c ? tmp : c;
}
