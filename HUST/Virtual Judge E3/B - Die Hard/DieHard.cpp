#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_WIDTH 80
#define MAX_BOMB_NUM 1010
#define MAX_DIST 5626
#define SQRT_2 1.4142135623730950488016887242097

typedef char Map[MAX_WIDTH + 1][MAX_WIDTH + 1];
typedef unsigned char Position[MAX_BOMB_NUM][2];
typedef double Distance[MAX_WIDTH + 1][MAX_WIDTH + 1];

void solveE3b_DieHard();
void inputMap(Map map, int rowNum, int colNum);
void inputBombs(Position bombs, int k);
double bfs(Map map, int rowNum, int colNum, unsigned char srcPos[2], unsigned char destPos[2]);
void initDistance(Distance d, int rowNum, int colNum, int value);
void copyPosition(unsigned char dest[2], unsigned char src[2]);
int canGo(Map map, int rowNum, int colNum, unsigned char position[2]);
void printDistance(Distance map, int rowNum, int colNum);

int main() {
	solveE3b_DieHard();
	return 0;
}

void solveE3b_DieHard() {
	int n, m, k;
	double v;
	Map map;
	Position bombs;

	scanf("%d %d %d %lf", &n, &m, &k, &v);
	inputMap(map, m, n);
	inputBombs(bombs, k);

	double totalDist = 0, currDist;
	unsigned char srcPos[2] = {bombs[0][0], bombs[0][1]};
	for (int i = 1; i <= k; ++i) {
		currDist = bfs(map, m, n, srcPos, bombs[i]);
		if (currDist < MAX_DIST) {
			totalDist += currDist;
			copyPosition(srcPos, bombs[i]);
		}
	}
	printf("%.2lf\n", totalDist / v);
}

void inputMap(Map map, int rowNum, int colNum) {
	for (int i = 1; i <= rowNum; ++i) {
		for (int j = 1; j <= colNum;) {
			scanf("%c", &map[i][j]);
			if (map[i][j] != '\n') ++j;
		}
	}
}

void inputBombs(Position bombs, int k) {
	int x, y;
	for (int i = 0; i <= k; ++i) {
		scanf("%d %d", &x, &y);
		bombs[i][0] = y;
		bombs[i][1] = x;
	}
		
}

unsigned char queue[MAX_WIDTH*MAX_WIDTH][2];
Distance distance;
double bfs(Map map, int rowNum, int colNum, unsigned char srcPos[2], unsigned char destPos[2]) {
	initDistance(distance, rowNum, colNum, MAX_DIST);
	
	int front = 0, rear = 0;
	copyPosition(queue[rear++], srcPos);
	distance[srcPos[0]][srcPos[1]] = 0;

	unsigned char currPos[2], nextPos[2];
	int neighbours[][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }, 
							{ -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
	double currDist;
	while (front != rear) {
		copyPosition(currPos, queue[front++]);
		for (int i = 0; i < 8; ++i) {
			nextPos[0] = currPos[0] + neighbours[i][0];
			nextPos[1] = currPos[1] + neighbours[i][1];
			if (canGo(map, rowNum, colNum, nextPos)) {
				if (i < 4) 
					currDist = distance[currPos[0]][currPos[1]] + 1;
				else
					currDist = distance[currPos[0]][currPos[1]] + SQRT_2;
				if (currDist < distance[nextPos[0]][nextPos[1]]) {
					distance[nextPos[0]][nextPos[1]] = currDist;
					copyPosition(queue[rear++], nextPos);
				}
			}
		}
	}
	// printDistance(distance, rowNum, colNum);
	return distance[destPos[0]][destPos[1]];
}

void copyPosition(unsigned char dest[2], unsigned char src[2]) {
	dest[0] = src[0];
	dest[1] = src[1];
}

void initDistance(Distance d, int rowNum, int colNum, int value) {
	for (int i = 1; i <= rowNum; ++i) {
		for (int j = 1; j <= colNum; ++j) {
			d[i][j] = value;
		}
	}
}

int canGo(Map map, int rowNum, int colNum, unsigned char position[2]) {
	return (position[0] >= 1 && position[0] <= rowNum 
			&& position[1] >= 1 && position[1] <= colNum 
			&& map[position[0]][position[1]] != '#');
}

void printDistance(Distance map, int rowNum, int colNum) {
	printf("\n");
	for (int i = 1; i <= rowNum; ++i) {
		for (int j = 1; j <= colNum; ++j)
			if (map[i][j] < MAX_DIST)
				printf("%04.2f ", map[i][j]);
			else
				printf("#### ");
		printf("\n");
	}
}