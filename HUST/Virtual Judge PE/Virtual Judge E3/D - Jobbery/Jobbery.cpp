#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 2001

typedef short Connection[MAX_N][MAX_N];

void solveE3d_Jobbery();
short inputConnection(Connection connection);
void tarjan(int n);
void strongConnect(int v);

int main() {
    solveE3d_Jobbery();
    return 0;
}

Connection connection;
int sccIdLut[MAX_N], sccInDegree[MAX_N], sccIdCnt = 0;
void solveE3d_Jobbery() {
    short n = inputConnection(connection);

    tarjan(n);

    for (int i = 1; i <= n; ++i) {
        int sccId = sccIdLut[i];
        for (int j = 0; connection[i][j] != 0; ++j) {
            if (sccIdLut[i] != sccIdLut[connection[i][j]])
                ++sccInDegree[sccIdLut[connection[i][j]]];
        }
    }

    short zeroInDegId, zeroInDegCnt = 0;
    for (int i = 1; i <= sccIdCnt; ++i) {
        if (sccInDegree[i] == 0) {
            zeroInDegId = i;
            ++zeroInDegCnt;
        }
    }

    if (zeroInDegCnt != 1) {
        printf("0\n");
        return;
    }

    for (int i = 1; i <= n; ++i) {
        if (sccIdLut[i] == zeroInDegId) {
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

int lowLink[MAX_N], stack[MAX_N], index[MAX_N], indexCnt = 0, top = 0;
bool onStack[MAX_N];
void tarjan(int n) {
    for (int i = 1; i <= n; ++i) {
        onStack[i] = false;
        index[i] = 0;
        sccIdLut[i] = 0;
    }

    indexCnt = 0;
    top = 0;

    for (int v = 1; v <= n; ++v) {
        if (index[v] == 0) {
            strongConnect(v);
        }
    }
}

void strongConnect(int v) {
    index[v] = lowLink[v] = ++indexCnt;
    stack[++top] = v;
    onStack[v] = true;

    for (int i = 0; connection[v][i] != 0; ++i) {
        int w = connection[v][i];
        if (index[w] == 0) {
            strongConnect(w);
            lowLink[v] = lowLink[v] < lowLink[w] ? lowLink[v] : lowLink[w];
        } else if (onStack[w]) {
            lowLink[v] = lowLink[v] < index[w] ? lowLink[v] : index[w];
        }
    }

    if (lowLink[v] == index[v]) {
        ++sccIdCnt;
        int w;
        do {
            w = stack[top--];
            onStack[w] = false;
            sccIdLut[w] = sccIdCnt;
        } while (v != w);
    }
}
