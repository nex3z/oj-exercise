#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 101;

typedef int Graph[MAX_N][MAX_N];

void solveE7e_MalevichStrikesBack();
int input(Graph g);
int size(Graph g, int n, int row, int col, int height);

int main() {
    // freopen("test.txt", "r", stdin);
    solveE7e_MalevichStrikesBack();
    return 0;
}

Graph g, wCnt, bCnt;
void solveE7e_MalevichStrikesBack() {
    int n = input(g);

    while (n != 0) {
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                //printf("%d %d\n", i, j);
                if (g[i][j] == 0 && g[i][j - 1] == 1 && g[i][j + 1] == 1) {
                    int height = 0;
                    for (height = i + 1; height <= n; ++height) {
                        if (g[height][j] == 0 && g[height][j - 1] == 1 && g[height][j + 1] == 1)
                            break;
                    }
                    height = height - i + 1;
                    if (height >= 3) {
                        int currSize = size(g, n, i, j, height);
                        result = result > currSize ? result : currSize;
                    }
                }
            }
        }
        if (result) {
            printf("%d\n", result);
        } else {
            printf("No solution\n");
        }
        
        n = input(g);
    }
}

int input(Graph g) {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &g[i][j]);
        }
    }

    return n;
}

int size(Graph g, int n, int row, int col, int height) {
    for (int i = 0; i <= height/2; ++i) {
        for (int j = 0; j <= i; ++j) {
            if ((col + j) > n || (col - j) < 0 || g[row + i][col + j] != 0 || g[row + i][col - j] != 0) {
                return 0;
            }
            if (g[row + height - 1 - i][col + j] != 0 || g[row + height - 1 - i][col - j] != 0) {
                return 0;
            }
        }
        for (int j = i + 1; j <= height/2; ++j) {
            if ((col + j) > n || (col - j) < 0 || g[row + i][col + j] != 1 || g[row + i][col - j] != 1) {
                return 0;
            }
            if (g[row + height - 1 - i][col + j] != 1 || g[row + height - 1 - i][col - j] != 1) {
                return 0;
            }
        }
    }
    return height;
}