#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_STATION_NUM 210
#define MAX_TIME 10000000

typedef double Map[MAX_STATION_NUM + 2][MAX_STATION_NUM + 2];
void solveE2A_ByTheUndergroundOrByFoot();
int inputMap(Map map);
void initMap(Map map, int n, double value);
double distance(double srcX, double srcY, double destX, double destY);
double dijkstra(Map g, int vNum, int src, unsigned char path[]);
void printMap(Map map, int n);

int main() {
    solveE2A_ByTheUndergroundOrByFoot();
    return 0;
}

Map map;
void solveE2A_ByTheUndergroundOrByFoot() {
    int stationNum = inputMap(map);
    unsigned char path[MAX_STATION_NUM + 2];
    // printMap(map, stationNum + 2);
    printf("%.20f\n", dijkstra(map, stationNum + 2, 0, path));
    printf("%d ", path[0] - 1);
    for (int i = path[0] - 1; i > 0; --i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int inputMap(Map map) {
    double footSpeed, ugSpeed, posX[MAX_STATION_NUM + 1], posY[MAX_STATION_NUM + 1];
    int stationNum;

    scanf("%lf %lf", &footSpeed, &ugSpeed);
    scanf("%d", &stationNum);

    for (int i = 1; i <= stationNum; ++i) {
        scanf("%lf %lf", &posX[i], &posY[i]);
    }

    initMap(map, stationNum + 2, -1);

    int srcId, destId;
    double dist, time;

    scanf("%d %d", &srcId, &destId);

    while (srcId != 0 || destId != 0) {
        dist = distance(posX[srcId], posY[srcId], posX[destId], posY[destId]);
        time = dist / ugSpeed;
        map[srcId][destId] = time;
        map[destId][srcId] = time;
        scanf("%d %d", &srcId, &destId);
    }

    scanf("%lf %lf", &posX[0], &posY[0]);
    scanf("%lf %lf", &posX[stationNum + 1], &posY[stationNum + 1]);

    for (int i = 0; i <= stationNum + 1; ++i) {
        for (int j = 0; j <= stationNum + 1; ++j) {
            if (i != j && map[i][j] < 0) {
                dist = distance(posX[i], posY[i], posX[j], posY[j]);
                time = dist / footSpeed;
                map[i][j] = time;
                map[j][i] = time;
            }
        }
    }

    return stationNum;
}

void initMap(Map map, int n, double value) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            map[i][j] = value;
        }
    }
}

double distance(double srcX, double srcY, double destX, double destY) {
    return sqrt(pow((srcX - destX), 2) + pow((srcY - destY), 2));
}

int getNearestUnknownVertex(double dist[], char isKnown[], int vNum) {
    int i, index;
    double min;

    for (i = 0, min = MAX_TIME, index = -1; i < vNum; ++i) {
        if ((!isKnown[i]) && (dist[i] >= 0) && (dist[i] < min)) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

double dijkstra(Map g, int vNum, int src, unsigned char path[]) {
    double dist[MAX_STATION_NUM + 2];
    char isKnown[MAX_STATION_NUM + 2];
    int v, u, i, j;
    unsigned char prev[MAX_STATION_NUM + 2];

    for (i = 0; i < vNum; ++i) {
        dist[i] = g[src][i];
        isKnown[i] = 0;
        prev[i] = src;
    }

    dist[src] = 0;
    isKnown[src] = 1;

    for (i = 0; i < vNum - 1; ++i) {
        u = getNearestUnknownVertex(dist, isKnown, vNum);
        isKnown[u] = 1;
        for (v = 0; v < vNum; ++v) {
            if (!isKnown[v] && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
                prev[v] = u;
            }
        }
    }

    for (i = vNum - 1, j = 1; i != src; i = prev[i], ++j) {
        path[j] = prev[i];
    }
    path[0] = j - 1;
    return dist[vNum - 1];
}

void printMap(Map map, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%6f ", map[i][j]);
        }
        printf("\n");
    }
}