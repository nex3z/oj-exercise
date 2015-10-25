#include <cstdio>

#define MAX_PATTERN_NUM 65536
#define FLAG -1

void solveUral1122_Game();
int inputPattern(int width);
void inputMove(int move[]);

int main() {
	// freopen("test.txt", "r", stdin);
	solveUral1122_Game();
	return 0;
}

int queue[MAX_PATTERN_NUM];
bool visited[MAX_PATTERN_NUM];
void solveUral1122_Game() {
	int initPattern = inputPattern(4);

	int move[16];
	inputMove(move);

	int front = 0, rear = 0;
	queue[rear++] = initPattern;
	visited[initPattern] = true;
	queue[rear++] = FLAG;

	int stepNum = 0;
	bool found = false;
	while (front != rear) {
		int curr = queue[front++];

		if (curr == FLAG) {
			if (front != rear) {
				++stepNum;
				queue[rear++] = FLAG;
				continue;
			}
		} else if (curr == 65535 || curr == 0) {
			found = true;
			break;
		}

		for (int i = 0; i < 16; ++i) {
			int next = curr ^ move[i];
			if (!visited[next]) {
				queue[rear++] = next;
				// printf("%d\n", rear);
				visited[next] = true;
			}
		}
	}

	if (found) {
		printf("%d\n", stepNum);
	} else {
		printf("Impossible\n");
	}

}

int inputPattern(int width) {
	char ch;
	int result = 0;
	for (int i = 0, cnt = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j, ++cnt) {
			scanf("%c", &ch);
			if (ch == 'W')
				result += 1 << cnt;
		}
		getchar();
	}
	return result;
}

void inputMove(int move[]) {
	char initMove[9];
	int shift[6][6] = {
			{ -1, -1, -1, -1, -1, -1 },
			{ -1,  0,  1,  2,  3, -1 },
			{ -1,  4,  5,  6,  7, -1 },
			{ -1,  8,  9, 10, 11, -1 },
			{ -1, 12, 13, 14, 15, -1 },
			{ -1, -1, -1, -1, -1, -1 } };
	int pos[9][2] = { 
			{ -1, -1 }, { -1, 0 }, { -1, 1 }, 
			{ 0, -1 }, { 0, 0 }, { 0, 1 }, 
			{ 1, -1 }, { 1, 0 }, { 1, 1 } };

	for (int i = 0; i < 9;) {
		scanf("%c", &initMove[i]);
		if (initMove[i] != '\n')
			++i;
	}

	for (int i = 1, cnt = 0; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j, ++cnt) {
			move[cnt] = 0;
			for (int k = 0; k < 9; ++k) {
				int row = i + pos[k][0], col = j + pos[k][1];
				if (shift[row][col] != -1 && initMove[k] == '1') {
					move[cnt] += 1 << shift[row][col];
				}
			}
		}
	}
}
