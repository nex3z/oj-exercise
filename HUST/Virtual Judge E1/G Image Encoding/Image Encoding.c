#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COORDINATE 10
#define MAX_POINTS ((MAX_COORDINATE + 1) * (MAX_COORDINATE + 1))

typedef char Image[MAX_COORDINATE + 1][MAX_COORDINATE + 1];

void solveE1g();
int inputImageFirst(Image image, int blackPixelNum, int *startX, int *startY);
int inputImageSecond(Image image, int startX, int startY);
void initImage(Image image);
void printSecondReprest(Image image, int blackPixelNum, int startX, int startY);
void printFirst(Image image, int startX, int startY, int blackPixelNum);
int hasBlackPixel(Image image, int x, int y);
void printImage(Image image, int size);

int main() {
    solveE1g();
    return 0;
}


Image image;
void solveE1g() {
    int blackPixelNum, startX, startY;
    char firstLine[10];

    scanf("%[^\n]", firstLine);
    if (strstr(firstLine, " ") == NULL) {
        sscanf(firstLine, "%d", &blackPixelNum);
        if (blackPixelNum == 0)
            return;
        inputImageFirst(image, blackPixelNum, &startX, &startY);
        printSecondReprest(image, blackPixelNum, startX, startY);
    } else {
        sscanf(firstLine, "%d %d", &startX, &startY);
        blackPixelNum = inputImageSecond(image, startX, startY);
        //printImage(image, 5);
        printFirst(image, startX, startY, blackPixelNum);
    }
}

int inputImageSecond(Image image, int startX, int startY) {
    int hasMore = 1, front = 0, rear = 0, currX, currY;
    char currChar;
    unsigned char queueX[MAX_POINTS], queueY[MAX_POINTS];

    initImage(image);
    
    queueX[rear] = startX;
    queueY[rear] = startY;
    ++rear;
    image[startY][startX] = 1;

    while (1) {
        currX = queueX[front];
        currY = queueY[front];
        ++front;

        while (1) {
            scanf("%c", &currChar);
            if (currChar == 'T') {
                queueX[rear] = currX;
                queueY[rear] = currY + 1;
                ++rear;
                image[currY + 1][currX] = 1;
            }
            else if (currChar == 'B') {
                queueX[rear] = currX;
                queueY[rear] = currY - 1;
                ++rear;
                image[currY - 1][currX] = 1;
            }
            else if (currChar == 'L') {
                queueX[rear] = currX - 1;
                queueY[rear] = currY;
                ++rear;
                image[currY][currX - 1] = 1;
            }
            else if (currChar == 'R') {
                queueX[rear] = currX + 1;
                queueY[rear] = currY;
                ++rear;
                image[currY][currX + 1] = 1;
            }
            else if (currChar == ',') {
                break;
            }
            else if (currChar == '.') {
                return front;
            }
        }
    }
}

void printFirst(Image image, int startX, int startY, int blackPixelNum) {
    int i, j, cnt = 0;

    printf("%d\n", blackPixelNum);
    for (i = 0; i <= MAX_COORDINATE && cnt < blackPixelNum; ++i) {
        for (j = 0; j <= MAX_COORDINATE && cnt < blackPixelNum; ++j) {
            if (image[j][i] == 1) {
                printf("%d %d\n", i, j);
                ++cnt;
            }
        }
    }
}

int inputImageFirst(Image image, int blackPixelNum, int *startX, int *startY) {
    int i, x, y;

    initImage(image);

    for (i = 0; i < blackPixelNum; ++i) {
        scanf("%d %d", &x, &y);
        image[y][x] = 1;
        if (i == 0) {
            *startX = x;
            *startY = y;
        }
    }

    return 0;
}

void initImage(Image image) {
    int i, j;

    for (i = 1; i < MAX_COORDINATE + 1; ++i) {
        for (j = 1; j < MAX_COORDINATE + 1; ++j) {
            image[i][j] = 0;
        }
    }
}

void printSecondReprest(Image image, int blackPixelNum, int startX, int startY) {
    int front = 0, rear = 0, currentX, currentY, nextX, nextY;
    unsigned char queueX[MAX_POINTS], queueY[MAX_POINTS];

    printf("%d %d\n", startX, startY);

    queueX[rear] = startX;
    queueY[rear] = startY;
    ++rear;
    image[startY][startX] = 0;

    while (front < rear) {
        currentX = queueX[front];
        currentY = queueY[front];
        ++front;

        // Check right
        nextX = currentX + 1;
        nextY = currentY;
        if (hasBlackPixel(image, nextX, nextY)) {
            queueX[rear] = nextX;
            queueY[rear] = nextY;
            ++rear;
            image[nextY][nextX] = 0;
            printf("R");
        }

        // Check top
        nextX = currentX;
        nextY = currentY + 1;
        if (hasBlackPixel(image, nextX, nextY)) {
            queueX[rear] = nextX;
            queueY[rear] = nextY;
            ++rear;
            image[nextY][nextX] = 0;
            printf("T");
        }

        // Check left
        nextX = currentX - 1;
        nextY = currentY; //Y-axis is upside down.
        if (hasBlackPixel(image, nextX, nextY)) {
            queueX[rear] = nextX;
            queueY[rear] = nextY;
            ++rear;
            image[nextY][nextX] = 0;
            printf("L");
        }

        // Check bottom
        nextX = currentX;
        nextY = currentY - 1;
        if (hasBlackPixel(image, nextX, nextY)) {
            queueX[rear] = nextX;
            queueY[rear] = nextY;
            ++rear;
            image[nextY][nextX] = 0;
            printf("B");
        }
        if (front == rear)
            printf(".\n");
        else
            printf(",\n");
    }
}

int hasBlackPixel(Image image, int x, int y) {
    if (x < 1 || x > MAX_COORDINATE || y < 1 || y > MAX_COORDINATE) {
        return 0;
    }
    else {
        return image[y][x];
    }
}

void printImage(Image image, int size) {
    int i, j;

    for (i = size; i >= 1; --i) {
        for (j = 1; j <= size; ++j) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}
