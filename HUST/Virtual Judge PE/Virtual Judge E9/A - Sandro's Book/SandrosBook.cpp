#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 51;

void solveP9a_SandrosBook();

int main() {
    solveP9a_SandrosBook();
    return 0;
}

void solveP9a_SandrosBook() {
    int cnt[26], max = 0;
    char str[MAX_LENGTH], maxChar;
    scanf("%s", str);

    memset(cnt, 0, 26 * sizeof(int));

    for (int i = 0; i < strlen(str); ++i) {
        ++cnt[str[i] - 'a'];
    }

    for (int i = 0; i < 26; ++i) {
        if (cnt[i] > max) {
            max = cnt[i];
            maxChar = i + 'a';
        }
    }

    printf("%c\n", maxChar);
}
