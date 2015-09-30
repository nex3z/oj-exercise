#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_N = 51;
const int MAX_PROBLEM_NUM = 2 * MAX_N;

typedef bool Graph[MAX_PROBLEM_NUM][MAX_PROBLEM_NUM];

void solveE7f_TwoRounds();
int input(Graph graph, int n);

int main() {
    // freopen("test.txt", "r", stdin);
    solveE7f_TwoRounds();
}

Graph isSame;
int group[MAX_PROBLEM_NUM], queue[MAX_PROBLEM_NUM], numInGroup[MAX_PROBLEM_NUM], f[MAX_PROBLEM_NUM][MAX_PROBLEM_NUM], selectedGroupId[MAX_PROBLEM_NUM];;
bool used[MAX_PROBLEM_NUM];
void solveE7f_TwoRounds() {
    int n, m;
    scanf("%d %d", &n, &m);
    int problemNum = n * 2;
    int first = input(isSame, m);

    int front = 0, rear = 0, groupForRound1 = 1, groupForRound2 = 2, searchIdx = 1;
    queue[rear++] = first;
    group[first] = groupForRound1;

    while (front != rear) {
        int curr = queue[front++];
        for (int i = 1; i <= problemNum; ++i) {
            if (i != curr && isSame[curr][i]) {
                if (group[i] == 0) {
                    queue[rear++] = i;
                    group[i] = group[curr] == groupForRound1 ? groupForRound2 : groupForRound1;
                }
                else if (group[i] == group[curr]) {
                    printf("IMPOSSIBLE\n");
                    return;
                }
            }
        }

        if (front == rear) {
            for (; searchIdx <= problemNum; ++searchIdx) {
                if (group[searchIdx] == 0) {
                    groupForRound1 += 2;
                    groupForRound2 += 2;
                    queue[rear++] = searchIdx;
                    group[searchIdx] = groupForRound1;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= problemNum; ++i) {
        ++numInGroup[group[i]];
    }

    for (int i = 0; i <= problemNum; ++i) {
        for (int j = 0; j <= problemNum; ++j) {
            f[i][j] = -1;
        }
    }

    f[0][0] = 1;
    for (int i = 0; i<groupForRound2/2; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (f[i][j] != -1) {
                f[i + 1][j + numInGroup[i * 2 + 1]] = i * 2 + 1;
                f[i + 1][j + numInGroup[i * 2 + 2]] = i * 2 + 2;
            }
        }
    }
    if (f[groupForRound2 / 2][n] == -1) {
        printf("IMPOSSIBLE\n");
        return;
    }

    int cnt = 0;
    for (int i = groupForRound2 / 2, neededNum = n; neededNum != 0; --i, ++cnt) {
        selectedGroupId[cnt] = f[i][neededNum];
        neededNum -= numInGroup[selectedGroupId[cnt]];
    }

    for (int i = 1; i <= problemNum; ++i) {
        for (int j = 0; j < cnt; ++j) {
            if (group[i] == selectedGroupId[j]) {
                printf("%d ", i);
                used[i] = true;
                break;
            }
        }
    }
    printf("\n");

    for (int i = 1; i <= problemNum; ++i) {
        if (!used[i])
            printf("%d ", i);
    }
    printf("\n");

}

int input(Graph graph, int n) {
    int first = -1;
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = true;
        graph[b][a] = true;
        first = (first == -1 ? a : first);
    }
    return first;
}