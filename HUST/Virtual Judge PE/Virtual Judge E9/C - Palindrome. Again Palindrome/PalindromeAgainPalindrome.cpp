#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 20001;

void solveP9c_PalindromeAgainPalindrome();
bool isPalindrome(char *start, char *end);

int main() {
    solveP9c_PalindromeAgainPalindrome();
    return 0;
}

char str[MAX_LENGTH];
void solveP9c_PalindromeAgainPalindrome() {
    scanf("%s", str);

    int len = strlen(str);
    
    // S2 must not be empty.
    char *start = str + 1, *end = str + len - 1;
    while (!isPalindrome(start, end) && (end - start >= 0)) {
        ++start;
    }

    printf("%s", str);
    while (start - str > 0) {
        printf("%c", *--start);
    }
    printf("\n");
}

bool isPalindrome(char *start, char *end) {
    while (end - start >= 0) {
        if (*start != *end) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}
