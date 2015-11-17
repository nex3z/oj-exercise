#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 1001;

void solveP9b_Palindrome();

int main() {
    solveP9b_Palindrome();
    return 0;
}

char str[MAX_LENGTH];
void solveP9b_Palindrome() {
    scanf("%s", str);

    int len = strlen(str);
    int start = 0, end = 0, maxPalindrome = 1;
    for (int i = 0; i < len; ++i) {
        for (int j = 1; i - j >= 0 && i + j < len; ++j) {
            if (str[i - j] == str[i + j]) {
                if (j * 2 + 1 > maxPalindrome) {
                    maxPalindrome = j * 2 + 1;
                    start = i - j;
                    end = i + j;
                }
            }else {
                break;
            }
        }

        int k = i + 1;
        for (int j = 0; i - j >= 0 && k + j < len; ++j) {
            if (str[i - j] == str[k + j]) {
                if (j * 2 + 2 > maxPalindrome) {
                    maxPalindrome = j * 2 + 2;
                    start = i - j;
                    end = k + j;
                }
            } else {
                break;
            }
        }
    }

    for (int i = start; i <= end; ++i) {
        printf("%c", str[i]);
    }
    printf("\n");
}
