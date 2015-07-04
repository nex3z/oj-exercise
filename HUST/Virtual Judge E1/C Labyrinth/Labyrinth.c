#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 33
#define STAT_BLOCKED -1
#define STAT_VISITED 0
#define STAT_AVAILABLE 1


typedef char Labyrinth[MAX_WIDTH][MAX_WIDTH];

void solveE1c();
int inputLabyrinth(Labyrinth laby);
int getWalls(int startRow, int startCol, Labyrinth laby, int width);
int canGoNorth(int row, int col, Labyrinth laby, int width);
int canGoSouth(int row, int col, Labyrinth laby, int width);
int canGoWest(int row, int col, Labyrinth laby, int width);
int canGoEast(int row, int col, Labyrinth laby, int width);
void printLaby(Labyrinth laby, int width);

Labyrinth laby;

int main() {
    //freopen("test.txt", "r", stdin);
    solveE1c();
	system("pause");
    return 0;
}

void solveE1c() {
    int width = 0, walls = 0, wallpaperSize = 0;

    width = inputLabyrinth(laby);
	// printLaby(laby, width);
    walls = getWalls(0, 0, laby, width);
	// printLaby(laby, width);
	if (laby[width - 1][width - 1] != 'v') {
		walls += getWalls(width - 1, width - 1, laby, width);
		// printLaby(laby, width);
	}

    wallpaperSize = (walls - 4) * 9;
    printf("%d\n", wallpaperSize);
}

int inputLabyrinth(Labyrinth laby) {
    int width = 0, i = 0, j = 0;
	char c;

    scanf("%d\n", &width);
    for(i = 0; i < width; ++i) {
        for(j = 0; j < width;) {
			scanf("%c", &c);
			if (c == '\n')
				continue;
			else
				laby[i][j++] = c;
        }
    }

    return width;
}

char qRow[MAX_WIDTH * MAX_WIDTH];
char qCol[MAX_WIDTH * MAX_WIDTH];
int getWalls(int startRow, int startCol, Labyrinth laby, int width) {
    int front = 0, rear = 0, currRow = 0, currCol = 0, walls = 0, nextPosStatus = 0;

	qRow[rear] = startRow;
	qCol[rear] = startCol;
    ++rear;
	laby[startRow][startCol] = 'v';

    while (front < rear) {
        currRow = qRow[front];
        currCol = qCol[front];
        ++front;

        nextPosStatus = canGoNorth(currRow, currCol, laby, width);
        if (nextPosStatus == STAT_AVAILABLE) {
            qRow[rear] = currRow - 1;
            qCol[rear] = currCol;
            ++rear;
            laby[currRow - 1][currCol] = 'v';
        } else if (nextPosStatus == STAT_BLOCKED) {
            ++walls;
        }

        nextPosStatus = canGoSouth(currRow, currCol, laby, width);
        if (nextPosStatus == STAT_AVAILABLE) {
            qRow[rear] = currRow + 1;
            qCol[rear] = currCol;
            ++rear;
            laby[currRow + 1][currCol] = 'v';
        } else if (nextPosStatus == STAT_BLOCKED) {
            ++walls;
        }

        nextPosStatus = canGoWest(currRow, currCol, laby, width);
        if (nextPosStatus == STAT_AVAILABLE) {
            qRow[rear] = currRow;
            qCol[rear] = currCol - 1;
            ++rear;
            laby[currRow][currCol - 1] = 'v';
        } else if (nextPosStatus == STAT_BLOCKED) {
            ++walls;
        }

        nextPosStatus = canGoEast(currRow, currCol, laby, width);
        if (nextPosStatus == STAT_AVAILABLE) {
            qRow[rear] = currRow;
            qCol[rear] = currCol + 1;
            ++rear;
            laby[currRow][currCol + 1] = 'v';
        } else if (nextPosStatus == STAT_BLOCKED) {
            ++walls;
        }
    }

    return walls;
}

int canGo(int row, int col, Labyrinth laby, int width) {
    if (row < 0 || row >= width || col < 0 || col >= width) {
        return STAT_BLOCKED;
    } else if (laby[row][col] == '#') {
        return STAT_BLOCKED;
    } else if (laby[row][col] == 'v') {
        return STAT_VISITED;
    } else {
        return STAT_AVAILABLE;
    }
}

int canGoNorth(int row, int col, Labyrinth laby, int width) {
    int nextRow = row - 1, nextCol = col;
    return canGo(nextRow, nextCol, laby, width);
}

int canGoSouth(int row, int col, Labyrinth laby, int width) {
    int nextRow = row + 1, nextCol = col;
    return canGo(nextRow, nextCol, laby, width);
}

int canGoWest(int row, int col, Labyrinth laby, int width) {
    int nextRow = row, nextCol = col - 1;
    return canGo(nextRow, nextCol, laby, width);
}

int canGoEast(int row, int col, Labyrinth laby, int width) {
    int nextRow = row, nextCol = col + 1;
    return canGo(nextRow, nextCol, laby, width);
}

void printLaby(Labyrinth laby, int width) {
	int i, j;
	for (i = 0; i < width; ++i) {
		for (j = 0; j < width; ++j) {
			printf("%c ", laby[i][j]);
		}
		printf("\n");
	}
}
