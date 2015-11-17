#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 250001;

void solveP9d_StringTale();
int kmp(char target[], char pattern[], int table[]);
void buildTable(char pattern[], int table[]);

int main() {
    solveP9d_StringTale();
    return 0;
}

char target[MAX_LENGTH*2];
char pattern[MAX_LENGTH];
int table[MAX_LENGTH];
void solveP9d_StringTale() {
    int n;
    scanf("%d", &n);
    scanf("%s", target);
    scanf("%s", pattern);

    int targetLen = strlen(target);
    memcpy(target + targetLen, target, targetLen);
    target[targetLen + targetLen] = '\0';

    buildTable(pattern, table);
    int result = kmp(target, pattern, table);
    result = result > 0 ? (targetLen - result) : result;
    printf("%d\n", result);
}

int kmp(char target[], char pattern[], int table[]) {
    int m = 0, i = 0, targetLen = strlen(target), patternLen = strlen(pattern);

    while (m + i < targetLen) {
        if (pattern[i] == target[m + i]) {
            if (i == patternLen - 1) {
                return m;
            }
            ++i;
        } else {
            if (table[i] > -1) {
                m = m + i - table[i];
                i = table[i];
            } else {
                i = 0;
                ++m;
            }
        }
    }

    return -1;
}

void buildTable(char pattern[], int table[]) {
    int pos = 2, cnd = 0, len = strlen(pattern);
    table[0] = -1;
    table[1] = 0;

    while (pos < len) {
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
