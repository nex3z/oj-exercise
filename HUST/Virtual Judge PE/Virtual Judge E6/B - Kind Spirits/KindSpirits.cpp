#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_LEVEL = 31;
const int MAX_PLANET_PER_LEVEL = 31;
const int MAX_COST = 2147483647;

typedef int Cost[MAX_LEVEL][MAX_PLANET_PER_LEVEL];
typedef struct FeeRecord{
    int from, cost;
    struct FeeRecord *next;
} Fee;
typedef Fee *Map[MAX_LEVEL][MAX_PLANET_PER_LEVEL];

void solveE6b_KindSpirits();
void inputMap(Map map, int levelNum, int planetNum[]);

int main() {
    solveE6b_KindSpirits();
    return 0;
}

Map map;
int cost[MAX_LEVEL][MAX_PLANET_PER_LEVEL];
int planetNum[MAX_LEVEL];
void solveE6b_KindSpirits() {
    int n;
    scanf("%d", &n);
    inputMap(map, n, planetNum);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < MAX_PLANET_PER_LEVEL; ++j) {
            cost[i][j] = MAX_COST;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= planetNum[i]; ++j) {
            Fee *f = map[i][j];
            
            int min = MAX_COST;
            while (f) {
                if (cost[i - 1][f->from] != MAX_COST) {
                    int curr = cost[i - 1][f->from] + f->cost;
                    min = min < curr ? min : curr;
                }
                f = f->next;
            }
            
            cost[i][j] = min;
        }
    }
    
    int result = cost[n][1];
    for (int i = 2; i <= planetNum[n]; ++i)
    result = result < cost[n][i] ? result : cost[n][i];
    
    printf("%d\n", result);
}

void inputMap(Map map, int levelNum, int planetNum[]) {
    for (int i = 1; i <= levelNum; ++i) {
        int num;
        scanf("%d", &num);
        planetNum[i] = num;
        
        for (int j = 1; j <= num; ++j) {
            int from, cost;
            scanf("%d", &from);
            while (from != 0) {
                scanf("%d", &cost);
                
                Fee *f = new Fee();
                f->from = from;
                f->cost = cost;
                f->next = map[i][j];
                map[i][j] = f;
                
                scanf("%d", &from);
            }
        }
        if (i != levelNum) {
            char c;
            scanf("%c", &c);
            while (c != '*')
            scanf("%c", &c);
        }
    }
}