#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 75010;

void solveP9e_JacksLastWord();
int kmp(char target[], char pattern[], int table[], int sep[]);
void buildTable(char pattern[], int table[]);

int main() {
    // freopen("test.txt", "r", stdin);
    solveP9e_JacksLastWord();
    return 0;
}

char target[MAX_LENGTH], pattern[MAX_LENGTH];
int table[MAX_LENGTH], sep[MAX_LENGTH];
void solveP9e_JacksLastWord() {
    scanf("%s", pattern);
    scanf("%s", target);

    buildTable(pattern, table);
    int result = kmp(target, pattern, table, sep);

    if (result < 0) {
        printf("Yes\n");
    } else {
        printf("No\n");
        int cnt = 0;
        for (int i = 0; i < result; ++i) {
            for (; cnt < sep[i]; ++cnt) {
                printf("%c", target[cnt]);
            }
            printf(" ");
        }
        int targetLen = strlen(target);
        while (cnt < targetLen) {
            printf("%c", target[cnt++]);
        }
        printf("\n");
    }
}

int kmp(char target[], char pattern[], int table[], int sep[]) {
    int m = 0, i = 0, cnt = 0, targetLen = strlen(target);

    while (m + i < targetLen) {
        if (pattern[i] == target[m + i]) {
            ++i;
        } else {
            if (table[i] > -1) {
                m = m + i - table[i];
                i = table[i];
                sep[cnt++] = m;
            } else {
                i = 0;
                ++m;
                return -1;
            }
        }
    }

    return cnt;
}

void buildTable(char pattern[], int table[]) {
    int pos = 2, cnd = 0, len = strlen(pattern);
    table[0] = -1;
    table[1] = 0;

    while (pos <= len) {
        if (pattern[pos - 1] == pattern[cnd]) {
            ++cnd;
            table[pos] = cnd;
            ++pos;
        } else if (cnd > 0) {
            cnd = table[cnd];
        } else {
            table[pos] = 0;
            ++pos;
        }
    }
}
