#include <cstdio>
 
#define MAX_LENGTH 100000
 
void solveUral1494_Monobilliards();
 
int main() {
	solveUral1494_Monobilliards();
	return 0;
}
 
int stack[MAX_LENGTH];
void solveUral1494_Monobilliards() {
	int n;
	scanf("%d", &n);
 
	int curr, top = 0, cnt = 1;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &curr);
		while (stack[top] != curr && cnt <= n) {
			stack[++top] = cnt;
			++cnt;
		}
		if (stack[top] == curr && top != 0)
			--top;
	}
 
	if (top != 0) {
		printf("Cheater\n");
	} else {
		printf("Not a proof\n");
	}
}
