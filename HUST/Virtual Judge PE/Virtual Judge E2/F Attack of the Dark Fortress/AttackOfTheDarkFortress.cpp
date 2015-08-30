#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#define MAX_SIZE 100
// #define DEBUG 1

struct PositionRecord;
typedef struct PositionRecord Position;
typedef Position *PtrToPosition;

struct PositionRecord {
    int row;
    int col;
    int time;
};

typedef char Map[MAX_SIZE][MAX_SIZE];
typedef int Distance[MAX_SIZE][MAX_SIZE];

void solveE2f();
void inputMap(Map map, int height, int width);
int getTime(Map map, int height, int width);
void getSpecialPosition(Map map, int height, int width, PtrToPosition posFortress, PtrToPosition posCatherine, PtrToPosition posGelu, vector<Position> teleports[]);
void setPosition(PtrToPosition p, int row, int col);
int getAvailablePosition(Map map, int height, int width, Position pos, PtrToPosition available);
int isAvailable(Map map, int height, int width, int row, int col);
void printMap(Map map, int height, int width);
void printDist(Distance map, int height, int width);

int main() {
    solveE2f();
    return 0;
}

Map map;
void solveE2f() {
    int height, width, time;

    scanf("%d %d", &height, &width);
    inputMap(map, height, width);
    time = getTime(map, height, width);
    if (time == -1)
        printf("Impossible\n");
    else
        printf("%d\n", time);
}

void inputMap(Map map, int height, int width) {
    int i, j;
    char mark;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width;) {
            scanf("%c", &mark);
            if (mark != '\n') {
                map[i][j++] = mark;
            }
        }
    }
}

Position queueCath[MAX_SIZE * MAX_SIZE], queueGelu[MAX_SIZE * MAX_SIZE];
Position queue[MAX_SIZE * MAX_SIZE];
Distance distCath, distGelu;
vector<Position> teleports[26];
int getTime(Map map, int height, int width) {
    int qCathFront, qCathRear, qGeluFront, qGeluRear;
    int front = 0, rear = 0, time = 0, availableNum, i, j, canGoToFortress, candTime;
    int offsetRow[8] = { -1, -1, 0, +1, +1, +1, 0, -1 }, offsetCol[8] = { 0, +1, +1, +1, 0, -1, -1, -1 }, fRow, fCol;
    Position posFortress, posCath, posGelu, posCurr, posAvailable[8], posNext, posTmp;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            distCath[i][j] = -1;
            distGelu[i][j] = -1;
        }
    }

    posCath.time = 0;
    posGelu.time = 0;
    getSpecialPosition(map, height, width, &posFortress, &posCath, &posGelu, teleports);

    queue[rear++] = posCath;
    distCath[posCath.row][posCath.col] = 0;
    canGoToFortress = 0;
    while (front != rear) {
        posCurr = queue[front++];
        availableNum = getAvailablePosition(map, height, width, posCurr, posAvailable);
        for (i = 0; i < availableNum; ++i) {
            posNext = posAvailable[i];
            posNext.time = posCurr.time + 1;
            if (map[posNext.row][posNext.col] == '*') {
                canGoToFortress = 1;
                if (distCath[posNext.row][posNext.col] == -1)
                    distCath[posNext.row][posNext.col] = posNext.time;
            } else if ((map[posNext.row][posNext.col] == '.' || map[posNext.row][posNext.col] == '!') && distCath[posNext.row][posNext.col] == -1) {
                queue[rear++] = posNext;
                distCath[posNext.row][posNext.col] = posNext.time;
            } else if (map[posNext.row][posNext.col] >= 'A' && map[posNext.row][posNext.col] <= 'Z') {
                for (j = 0; j < teleports[map[posNext.row][posNext.col] - 'A'].size(); ++j) {
                    posTmp = teleports[map[posNext.row][posNext.col] - 'A'].at(j);
                    if (distCath[posTmp.row][posTmp.col] == -1) {
                        posTmp.time = posNext.time;
                        queue[rear++] = posTmp;
                        distCath[posTmp.row][posTmp.col] = posTmp.time;
                    } else {
                        break;
                    }
                }
            }
        }
    }
#ifdef DEBUG
    printDist(distCath, height, width);
#endif
    if (canGoToFortress == 0) {
        return -1;
    }

    rear = 0;
    front = 0;
    queue[rear++] = posGelu;
    distGelu[posGelu.row][posGelu.col] = 0;
    canGoToFortress = 0;
    while (front != rear) {
        posCurr = queue[front++];
        availableNum = getAvailablePosition(map, height, width, posCurr, posAvailable);
        for (i = 0; i < availableNum; ++i) {
            posNext = posAvailable[i];
            posNext.time = posCurr.time + 1;
            if (map[posNext.row][posNext.col] == '*') {
                canGoToFortress = 1;
                if (distGelu[posNext.row][posNext.col] == -1)
                    distGelu[posNext.row][posNext.col] = posNext.time;
            }
            else if ((map[posNext.row][posNext.col] == '.' || map[posNext.row][posNext.col] == '$') && distGelu[posNext.row][posNext.col] == -1) {
                queue[rear++] = posNext;
                distGelu[posNext.row][posNext.col] = posNext.time;
            }
            else if (map[posNext.row][posNext.col] >= 'A' && map[posNext.row][posNext.col] <= 'Z') {
                for (j = 0; j < teleports[map[posNext.row][posNext.col] - 'A'].size(); ++j) {
                    posTmp = teleports[map[posNext.row][posNext.col] - 'A'].at(j);
                    if (distGelu[posTmp.row][posTmp.col] == -1) {
                        posTmp.time = posNext.time;
                        queue[rear++] = posTmp;
                        distGelu[posTmp.row][posTmp.col] = posTmp.time;
                    } else {
                        break;
                    }
                }
            }
        }
    }
#ifdef DEBUG
    printDist(distGelu, height, width);
#endif
    if (canGoToFortress == 0) {
        return -1;
    }

    time = MAX_SIZE * MAX_SIZE + 1;
    for (i = 0; i < 8; ++i) {
        fRow = posFortress.row + offsetRow[i];
        fCol = posFortress.col + offsetCol[i];
        if (fRow >= 0 && fRow < height && fCol >= 0 && fCol < width) {
            if (distCath[fRow][fCol] != -1 && distGelu[fRow][fCol] != -1) {
                candTime = distCath[fRow][fCol] > distGelu[fRow][fCol] ? distCath[fRow][fCol] : distGelu[fRow][fCol];
                if (time > candTime) {
                    time = candTime;
                }
            }
        }
    }
    
    if (time == MAX_SIZE * MAX_SIZE + 1)
        return -1;
    else
        return time + 1;
}

void getSpecialPosition(Map map, int height, int width, PtrToPosition posFortress, PtrToPosition posCatherine, PtrToPosition posGelu, vector<Position> teleports[]) {
    int i, j;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            if (map[i][j] == '*')
                setPosition(posFortress, i, j);
            else if (map[i][j] == '$')
                setPosition(posCatherine, i, j);
            else if (map[i][j] == '!')
                setPosition(posGelu, i, j);
            else if (map[i][j] >= 'A' && map[i][j] <= 'Z') {
                PtrToPosition p = (PtrToPosition)malloc(sizeof(Position));
                setPosition(p, i, j);
                teleports[map[i][j] - 'A'].push_back(*p);
                //free(p);
            }
        }
    }
}

int getAvailablePosition(Map map, int height, int width, Position pos, PtrToPosition available) {
    int num = 0, row, col, i, offsetRow[8] = {-1, -1, 0, +1, +1, +1, 0, -1}, offsetCol[8] = {0, +1, +1, +1, 0, -1, -1, -1};

    for (i = 0; i < 8; ++i) {
        row = pos.row + offsetRow[i];
        col = pos.col + offsetCol[i];
        if (isAvailable(map, height, width, row, col))
            setPosition(&available[num++], row, col);
    }
    return num;
}

int isAvailable(Map map, int height, int width, int row, int col) {
    if (row >= 0 && row < height && col >= 0 && col < width && map[row][col] != '#')
        return 1;
    else
        return 0;
}

void setPosition(PtrToPosition p, int row, int col) {
    p->row = row;
    p->col = col;
}

void printMap(Map map, int height, int width) {
    int i, j;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void printDist(Distance map, int height, int width) {
    int i, j;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            printf("%2d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}