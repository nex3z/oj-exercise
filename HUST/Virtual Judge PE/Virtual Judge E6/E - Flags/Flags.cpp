#include <cstdio>

const int MAX_N = 46;

void solveE6e_Flags();

int main() {
    solveE6e_Flags();
}

long long int cnt[MAX_N];
void solveE6e_Flags() {
    int n;
    scanf("%d", &n);
    
    cnt[1] = cnt[2] = 2;
    for (int i = 3; i <= n; ++i)
    cnt[i] = cnt[i - 1] + cnt[i - 2];
    
    printf("%lld\n", cnt[n]);
}