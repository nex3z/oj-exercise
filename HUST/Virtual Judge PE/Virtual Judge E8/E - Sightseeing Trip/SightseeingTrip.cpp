#include <cstdio>

const int MAX_N = 101;
const int MAX_DIST = 30000;
typedef int Graph[MAX_N][MAX_N];

void solveP8e_SightseeingTrip();
void inputMap(Graph map, int n, int m);
int floyd(Graph map, int n, int result[]);

int main() {
    // freopen("test.txt", "r", stdin);
    solveP8e_SightseeingTrip();
    return 0;
}

Graph map;
int result[MAX_N];
void solveP8e_SightseeingTrip() {
    while (1) {
        int n, m;
        if (scanf("%d %d", &n, &m) == 1)
            return;

        inputMap(map, n, m);

        int cnt = floyd(map, n, result);

        if (cnt) {
            for (int i = 0; i < cnt; ++i) {
                printf("%d ", result[i]);
            }
            printf("\n");
        } else {
            printf("No solution.\n");
        }
    }
}

Graph dist, path;
int floyd(Graph map, int n, int result[]) {
    int currDist = MAX_DIST, cnt = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = map[i][j];
            path[i][j] = i;
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i) {
            for (int j = 1; j < i; ++j) {
                if (dist[i][j] + map[i][k] + map[k][j] < currDist) {
                    currDist = dist[i][j] + map[i][k] + map[k][j];
                    int currPos = j;
                    cnt = 0;
                    while (currPos != i) {
                        result[cnt++] = currPos;
                        currPos = path[i][currPos];
                    }
                    result[cnt++] = i;
                    result[cnt++] = k;
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    return cnt;
}

void inputMap(Graph map, int n, int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            map[i][j] = MAX_DIST;
        }
    }

    for (int i = 0; i < m; ++i) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        map[a][b] = map[a][b] < l ? map[a][b] : l;
        map[b][a] = map[a][b];
    }
}