#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <set>
#include <queue>

using namespace std;

#define MAX_N 1000
#define MAX_M 100000
#define CHANGE_BUS -1

void solveE5f_BusesInVasyuki();
void inputTransport(set<int> transport[], int routeNum);

int main() {
    solveE5f_BusesInVasyuki();
    return 0;
}

set<int> transport[MAX_N];
queue<int> q;
bool visitedStop[MAX_M], visitedRoute[MAX_N];
int pre[MAX_M], path[MAX_N];
void solveE5f_BusesInVasyuki() {
    int n, m, src, dest;
    scanf("%d %d", &n, &m);
    inputTransport(transport, n);
    scanf("%d %d", &src, &dest);

    q.push(src);
    pre[src] = -1;
    visitedStop[src] = true;
    q.push(CHANGE_BUS);
    int curr, fee = 0;
    bool found = false;
    while (!q.empty()) {
        curr = q.front();
        q.pop();

        if (curr == dest) {
            found = true;
            break;
        } else if (curr == CHANGE_BUS) {
            if (q.empty()) {
                break;
            }
            else {
                ++fee;
                q.push(CHANGE_BUS);
                continue;
            }            
        }

        for (int i = 0; i < n; ++i) {
            if (!visitedRoute[i]) {
                set<int>::iterator it = transport[i].find(curr);
                if (it != transport[i].end()) {
                    for (std::set<int>::iterator it2 = transport[i].begin(); it2 != transport[i].end(); ++it2) {
                        if (!visitedStop[*it2]) {
                            q.push(*it2);
                            pre[*it2] = curr;
                            visitedStop[*it2] = true;
                        }
                    }
                    visitedRoute[i] = true;
                }
            }
        }
    }
    if (found) {
        printf("%d\n", fee);
    } else {
        printf("-1\n");
        return;
    }
    int cnt = 0;
    for (int i = dest; i != -1; i = pre[i]) {
        path[cnt++] = i;
    }

    for (int i = cnt - 1; i >= 0; --i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void inputTransport(set<int> transport[], int routeNum) {
    int stopNum, stopId;
    for (int i = 0; i < routeNum; ++i) {
        scanf("%d", &stopNum);
        for (int j = 0; j < stopNum; ++j) {
            scanf("%d", &stopId);
            transport[i].insert(stopId);
        }
    }
}