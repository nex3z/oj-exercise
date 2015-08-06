#include <stdio.h>

#define MAX_N 101

typedef unsigned char Friends[MAX_N][MAX_N];

void solveE4f_TwoTeams();
int inputFriends(Friends friends);

int main() {
    solveE4f_TwoTeams();
    return 0;
}

Friends friends;
unsigned char inTeam[MAX_N];
bool hasFriendsInTeam1[MAX_N];
void solveE4f_TwoTeams() {
    int n = inputFriends(friends);
    int team1cnt = 0;

    for (int i = 1; i <= n; ++i) {
        if (!hasFriendsInTeam1[i]) {
            inTeam[i] = 1;
            ++team1cnt;
            for (int j = 1; j <= friends[i][0]; ++j) {
                hasFriendsInTeam1[friends[i][j]] = true;
            }
        }
    }

    printf("%d\n", team1cnt);
    for (int i = 1; i <= n; ++i) {
        if (inTeam[i] == 1)
            printf("%d ", i);
    }
    printf("\n");
}

int inputFriends(Friends friends) {
    int n;
    scanf("%d", &n);

    int friendId, cnt;
    for (int i = 1; i <= n; ++i) {
        cnt = 1;
        scanf("%d", &friendId);
        while (friendId != 0) {
            friends[i][cnt++] = friendId;
            scanf("%d", &friendId);
        }
        friends[i][0] = cnt - 1;
    }

    return n;
}