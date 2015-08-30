#include <stdio.h>

#define MAX_N 100000

void solveE5c_MonthlyExpense();
int inputBudget(short budget[], int n);
bool inRed(short budget[], int n, int monthBudget, int m);

int main() {
    solveE5c_MonthlyExpense();
}

short budget[MAX_N];
void solveE5c_MonthlyExpense() {
    int n, m;
    scanf("%d %d", &n, &m);

    int sum = inputBudget(budget, n);

    int l = 0, r = sum, mid = (l + r) / 2, ans;
    while (l <= r) {
        if (!inRed(budget, n, mid, m)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
        mid = (l + r) / 2;
    }

    printf("%d\n", ans);
}

int inputBudget(short budget[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &budget[i]);
        sum += budget[i];
    }

    return sum;
}

bool inRed(short budget[], int n, int monthBudget, int m) {
    int cnt = 1, current = 0;
    for (int i = 0; i < n; ++i) {
        if (budget[i] > monthBudget)
            return true;
        current += budget[i];
        if (current > monthBudget) {
            ++cnt;
            current = budget[i];
        }
    }

    if (cnt > m)
        return true;
    else
        return false;
}