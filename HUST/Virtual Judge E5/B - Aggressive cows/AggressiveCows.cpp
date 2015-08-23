#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

void solveE5B_AggressiveCows();
void inputPositions(int pos[], int n);
int cmp(const void *a, const void *b);
bool isSafe(int pos[], int n, int dist, int target);

int main() {
	solveE5B_AggressiveCows();
}

int positions[MAX_N];
void solveE5B_AggressiveCows() {
	int n, c;
	scanf("%d %d", &n, &c);

	inputPositions(positions, n);

	int l = positions[0], r = positions[n - 1], mid = (l + r) / 2;
	while (l <= r) {
		if (isSafe(positions, n, mid, c)) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
		mid = (l + r) / 2;
	}

	printf("%d\n", mid);
}

void inputPositions(int pos[], int n) {
	for (int i = 0; i < n; ++i) {
		scanf("%d", &pos[i]);
	}
	qsort(pos, n, sizeof(int), cmp);
}

int cmp(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

bool isSafe(int pos[], int n, int dist, int target) {
	int cnt = 1, start = pos[0];
	for (int i = 1; i < n; ++i) {
		if (pos[i] - start >= dist) {
			start = pos[i];
			++cnt;
		}
	}

	if (cnt >= target)
		return true;
	else
		return false;
}