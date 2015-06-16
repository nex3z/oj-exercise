#include <stdio.h>

#define MAX_COUNTRY_NUM 99
#define UNCONNECTED 0
#define CONNECTED 1
#define STAT_RED 0
#define STAT_BLUE 1
#define STAT_UNVISITED 2

typedef char Map[MAX_COUNTRY_NUM + 1][MAX_COUNTRY_NUM + 1];


void solveE1d();
int inputMap(Map map);
void initMap(Map map, int countryNum);
int colorMap(Map map, int countryNum, char stat[]);
int changeColor(int color);
void printStat(char stat[], int countryNum);
void printMap(Map map, int countryNum);

int main(int argc, const char * argv[]) {
    solveE1d();
    return 0;
}

Map map;
char countryStat[MAX_COUNTRY_NUM + 1];
void solveE1d() {
    int countryNum, result;

    countryNum = inputMap(map);
    // printMap(map, countryNum);
    result = colorMap(map, countryNum, countryStat);
    if (result == -1) {
        printf("-1\n");
    } else {
        printStat(countryStat, countryNum);
    }
}

int inputMap(Map map) {
    int countryNum, i, connected;
    
    scanf("%d", &countryNum);
    initMap(map, countryNum);
    
    for (i = 1; i <= countryNum;) {
        scanf("%d", &connected);
        if (connected != 0) {
            map[i][connected] = CONNECTED;
            map[connected][i] = CONNECTED;
        } else {
            ++i;
        }
    }
    
    return countryNum;
}

void initMap(Map map, int countryNum) {
    int i, j;
    
    for (i = 1; i <= countryNum; ++i) {
        for (j = 1; j <= countryNum; ++j) {
            map[i][j] = UNCONNECTED;
        }
    }
}

char queue[MAX_COUNTRY_NUM + 1];
int colorMap(Map map, int countryNum, char countryStat[]) {
    int i, front = 0, rear = 0, currCountry, currColor, nextColor,
        isolatedCountry = 1;
    
    for (i = 1; i <= countryNum; ++i) {
        countryStat[i] = STAT_UNVISITED;
    }
    
    queue[rear++] = 1;
    countryStat[1] = STAT_RED;
    
    while (front < rear) {
        currCountry = queue[front++];
        currColor = countryStat[currCountry];
        nextColor = changeColor(currColor);
        for (i = 1; i <= countryNum; ++i) {
            if (map[currCountry][i] == CONNECTED) {
                if (countryStat[i] == STAT_UNVISITED) {
                    queue[rear++] = i;
                    countryStat[i] = nextColor;
                } else if (countryStat[i] == currColor) {
                    return -1;
                }
            }
        }
        
        if (front == rear) {
            for (i = isolatedCountry; i <= countryNum; ++i) {
                if (countryStat[i] == STAT_UNVISITED) {
                    isolatedCountry = i;
                    queue[rear++] = i;
                    countryStat[i] = STAT_RED;
                    break;
                }
            }
        }
    }
    
    return 1;
}

int changeColor(int color) {
    if (color == STAT_RED) {
        return STAT_BLUE;
    } else {
        return STAT_RED;
    }
}

void printStat(char stat[], int countryNum) {
    int i;
    
    for (i = 1; i <= countryNum; ++i) {
        printf("%d", stat[i]);
    }
    printf("\n");
    
}

void printMap(Map map, int countryNum) {
    int i, j;
    
    for (i = 1; i <= countryNum; ++i) {
        for (j = 1; j <= countryNum; ++j) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}
