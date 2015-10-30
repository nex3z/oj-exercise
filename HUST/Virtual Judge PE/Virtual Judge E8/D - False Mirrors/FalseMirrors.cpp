#include <cstdio>

#define MAX_N 20
#define MAX_DAMAGE 20000

void solvePE8d_FalseMirrors();
int input(int balconies[]);
void dfs(int damage);
int getDamage();
void setDestoryed(int id, bool isDestoryed);
int getCode();

int main() {
    // freopen("test.txt", "r", stdin);
    solvePE8d_FalseMirrors();
    return 0;
}


bool destoryed[MAX_N], visited[1048576];
int balconies[MAX_N], n, minDamage = MAX_DAMAGE;
void solvePE8d_FalseMirrors() {
    n = input(balconies);

    for (int i = 0; i < n; ++i) {
        setDestoryed(i, true);
        int damage = getDamage();
        int code = getCode();
        if (visited[code] == false) {
            dfs(damage);
            visited[code] = true;
        }
        setDestoryed(i, false);
    }

    printf("%d\n", minDamage);

}

void printDes() {
    for (int i = 0; i < n; ++i) {
        if (destoryed[i]) {
            printf("1 ");
        }
        else {
            printf("0 ");
        }
    }
    printf("\n");

}

void dfs(int damage) {
    //printf("%d\n", damage);
    //printDes();
    if (damage > minDamage) {
        return;
    }
    bool hasMore = false, needRecover[2] = { false, false };
    for (int i = 0; i < n; ++i) {
        if (!destoryed[i]) {
            needRecover[0] = false;
            needRecover[1] = false;
            hasMore = true;
            destoryed[i] = true;
            int nextId = (i + 1) % n;
            if (destoryed[nextId] == false) {
                destoryed[nextId] = true;
                needRecover[1] = true;
            }
            int lastId = (i - 1) < 0 ? (n - 1) : (i - 1);
            if (destoryed[lastId] == false) {
                destoryed[lastId] = true;
                needRecover[0] = true;
            }

            int currDamage = damage + getDamage();
            int code = getCode();
            if (visited[code] == false) {
                visited[code] = true;
                dfs(currDamage);
                visited[code] = false;
            }

            destoryed[i] = false;
            if (needRecover[0]) {
                destoryed[lastId] = false;
            }
            if (needRecover[1]) {
                destoryed[nextId] = false;
            }

        }
    }

    if (!hasMore) {
        minDamage = minDamage < damage ? minDamage : damage;
    }

}

int getDamage() {
    int damage = 0;
    for (int i = 0; i < n; ++i) {
        if (!destoryed[i]) {
            damage += balconies[i];
        }
    }
    return damage;
}
int getCode() {
    int code = 0;
    for (int i = 0; i < n; ++i) {
        if (destoryed[i]) {
            code += 1 << i;
        }
    }
    return code;
}
void setDestoryed(int id, bool isDestoryed) {
    destoryed[id] = isDestoryed;
    destoryed[(id + 1) % n] = isDestoryed;
    destoryed[(id - 1) < 0 ? (n - 1) : (id - 1)] = isDestoryed;
}



int input(int balconies[]) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &balconies[i]);
    }

    return n;
}