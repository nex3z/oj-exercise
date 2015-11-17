#include <iostream>
#include <string>
using namespace std;

const int MAX_BRACKETS_NUM = 101;
const int MAX = 101;

void solveP9f_BracketsSequence();

int main() {
    solveP9f_BracketsSequence();
    return 0;
}

int dp[MAX_BRACKETS_NUM][MAX_BRACKETS_NUM];
string result[MAX_BRACKETS_NUM][MAX_BRACKETS_NUM], str;
void solveP9f_BracketsSequence() {
    cin >> str;
    int len = str.length();

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            dp[i][j] = MAX;
        }
    }

    for (int i = len - 1; i >= 0; i--) {
        for (int j = i; j < len; j++) {
            if (i == j) {
                dp[i][j] = 1;
                if (str[i] == '(' || str[i] == ')')
                    result[i][j] = "()";
                else
                    result[i][j] = "[]";
            } else {
                if (str[i] == '(' && str[j] == ')') {
                    if (dp[i + 1][j - 1] < dp[i][j]) {
                        result[i][j] = "(" + result[i + 1][j - 1] + ")";
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                } else if (str[i] == '[' && str[j] == ']') {
                    if (dp[i + 1][j - 1] < dp[i][j]) {
                        result[i][j] = "[" + result[i + 1][j - 1] + "]";
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                for (int k = i; k < j; k++) {
                    if (dp[i][j] > dp[i][k] + dp[k + 1][j]) {
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                        result[i][j] = result[i][k] + result[k + 1][j];
                    }
                }
            }
        }
    }

    cout << result[0][len - 1] << endl;
}