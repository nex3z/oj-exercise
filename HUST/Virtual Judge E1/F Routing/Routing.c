#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 90 
#define MAX_K 5

typedef char Network[MAX_N + 1][MAX_N + 1];
typedef unsigned char Subnet[MAX_N + 1][MAX_K + 1][4];

void solveE1f();
int inputNetwork(Network network);
void initNetwork(Network network, int computerNum);
int isInSameSubnet(int src, int dest, Subnet subnet, unsigned char ipNum[]);
int equals(unsigned char ip1[], unsigned char ip2[]);
int findPath(int src, int dest, Network network, int computerNum, unsigned char path[]);
void printPath(unsigned char path[], int pathLength);
void printNetwork(Network network, int computerNum);

int main() {
	//freopen("test.txt", "r", stdin);
	solveE1f();
	//system("pause");
	return 0;
}

Network network;
void solveE1f() {
	int computerNum, src, dest, pathLength;
	unsigned char path[MAX_N + 1];

	computerNum = inputNetwork(network);
	scanf("%d %d", &src, &dest);
	//printNetwork(network, computerNum);
	pathLength = findPath(src, dest, network, computerNum, path);
	if (pathLength == -1) {
		printf("No\n");
	}
	else
		printf("Yes\n");
		printPath(path, pathLength);
}

Subnet subnet;
unsigned char ipNum[MAX_N + 1];
int inputNetwork(Network network) {
	int computerNum, i, j, k;
	unsigned int ipAddr[4], mask[4];

	scanf("%d", &computerNum);
	initNetwork(network, computerNum);
	for (i = 1; i <= computerNum; ++i) {
		scanf("%d", &ipNum[i]);
		for (j = 0; j < ipNum[i]; ++j) {
			scanf("%d.%d.%d.%d %d.%d.%d.%d", &ipAddr[3], &ipAddr[2], &ipAddr[1], &ipAddr[0], &mask[3], &mask[2], &mask[1], &mask[0]);
			for (k = 0; k < 4; ++k) {
				subnet[i][j][k] = ipAddr[k] & mask[k];
			}
		}
	}

	for (i = 1; i <= computerNum; ++i) {
		for (j = 1; j <= computerNum; ++j) {
			if (i == j)
				continue;
			if (isInSameSubnet(i, j, subnet, ipNum)) {
				network[i][j] = 1;
				network[j][i] = 1;
			}
		}
	}
	 
	return computerNum;
}

void initNetwork(Network network, int computerNum) {
	int i, j;
	for (i = 0; i < computerNum; ++i) {
		for (j = 0; j < computerNum; ++j) {
			network[i][j] = 0;
		}
	}
}

int isInSameSubnet(int src, int dest, Subnet subnet, unsigned char ipNum[]) {
	int i, j;

	for (i = 0; i < ipNum[src]; ++i) {
		for (j = 0; j < ipNum[dest]; ++j) {
			if (equals(subnet[src][i], subnet[dest][j])) {
				return 1;
			}
		}
	}
	return 0;
}

int equals(unsigned char ip1[], unsigned char ip2[]) {
	int i;
	for (i = 0; i < 4; ++i) {
		if (ip1[i] != ip2[i])
			return 0;
	}
	return 1;
}


int findPath(int src, int dest, Network network, int computerNum, unsigned char path[]) {
	int i, front = 0, rear = 0, current, queuePos = 0, hasPath = 0;
	unsigned char queue[MAX_N + 1], last[MAX_N + 1], visited[MAX_N + 1];

	for (i = 1; i <= MAX_N; ++i) {
		visited[i] = 0;
	}

	queue[rear] = src;
	last[rear] = 0;
	++rear;
	visited[src] = 1;
	

	while (front < rear) {
		queuePos = front;
		current = queue[queuePos];
		++front;
		if (current == dest) {
			hasPath = 1;
			break;
		}

		for (i = 1; i <= computerNum; ++i) {
			if (network[current][i] == 1 && visited[i] == 0) {
				queue[rear] = i;
				last[rear] = queuePos;
				++rear;
				visited[i] = 1;
			}
		}
	}

	if (hasPath == 0)
		return -1;

	path[0] = current;
	queuePos = last[queuePos];
	i = 1;
	while (1) {
		path[i++] = queue[queuePos];
		if (queue[queuePos] == src)
			return i;
		queuePos = last[queuePos];
	}

}

void printPath(unsigned char path[], int pathLength) {
	int i;
	for (i = pathLength - 1; i >= 0; --i) {
		printf("%d ", path[i]);
	}
	printf("\n");
}

void printNetwork(Network network, int computerNum) {
	int i, j;
	for (i = 1; i <= computerNum; ++i) {
		for (j = 1; j <= computerNum; ++j) {
			printf("%d ", network[i][j]);
		}
		printf("\n");
	}
}
