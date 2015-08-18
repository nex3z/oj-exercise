#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 2001

typedef short Connection[MAX_N][MAX_N];

void solveE3d_Jobbery();
short inputConnection(Connection connection);
void tarjan(int u);

int main() {
    solveE3d_Jobbery();
    return 0;
}

Connection connection;
short sccCnt = 0;
short dfn[MAX_N], sccLUT[MAX_N], in[MAX_N];
void solveE3d_Jobbery() {
    short n = inputConnection(connection);

    for (int i = 1; i <= n; ++i) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        int sccId = sccLUT[i];
        for (int j = 0; connection[i][j] != 0; ++j) {
            if (sccLUT[i] != sccLUT[connection[i][j]])
                ++in[sccLUT[connection[i][j]]];
        }
    }

    short zeroInDegId, zeroInDegCnt = 0;
    for (int i = 1; i <= sccCnt; ++i) {
        if (in[i] == 0) {
            zeroInDegId = i;
            ++zeroInDegCnt;
        }
    }

    if (zeroInDegCnt != 1) {
        printf("0\n");
        return;
    }

    for (int i = 1; i <= n; ++i) {
        if (sccLUT[i] == zeroInDegId) {
            printf("%d ", i);
        }
    }
    printf("0\n");
}

short inputConnection(Connection connection) {
    int n;
    scanf("%d", &n);

    int senateId, cnt = 0;
    for (int i = 1; i <= n;) {
        scanf("%d", &senateId);
        connection[i][cnt++] = (short)senateId;
        if (senateId == 0) {
            ++i;
            cnt = 0;
        }
    }

    return n;
}

short low[MAX_N], stack[MAX_N], index = 1, top = 0;
bool inStack[MAX_N];
void tarjan(int u) {
    dfn[u] = low[u] = ++index;
    stack[++top] = u;
    inStack[u] = true;

    for (int i = 0; connection[u][i] != 0; ++i) {
        short currentId = connection[u][i];
        if (dfn[currentId] == 0) {
            tarjan(currentId);
            low[u] = low[u] < low[currentId] ? low[u] : low[currentId];
        }
        else {
            if (inStack[currentId]) {
                low[u] = low[u] < dfn[currentId] ? low[u] : dfn[currentId];
            }
        }
    }

    short id;
    if (dfn[u] == low[u]) {
        ++sccCnt;
        do {
            id = stack[top--];
            sccLUT[id] = sccCnt;
            inStack[id] = false;
        } while (u != id);
    }
}