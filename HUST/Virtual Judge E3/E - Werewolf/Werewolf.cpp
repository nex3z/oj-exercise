#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 1001
#define LINE_BUF_LEN 10

typedef struct RelationRecord{
    short id;
    struct RelationRecord *next;
} Relation;

void solveE3e_Werewolf();
int inputRelation(Relation *descendants[], Relation *ancestors[]);
void addRelation(Relation *relation[], int id, int newRelation);
void dfs(Relation *relation[], int id);

int main() {
    // freopen("test_2.txt", "r", stdin);
    solveE3e_Werewolf();
}

Relation *descendants[MAX_N], *ancestors[MAX_N];
bool isHuman[MAX_N];
void solveE3e_Werewolf() {
    int n = inputRelation(descendants, ancestors);

    char line[LINE_BUF_LEN];
    int victim;
    while (scanf("%[^\n]", line) != EOF) {
        getchar();
        sscanf(line, "%d", &victim);
        dfs(descendants, victim);
        dfs(ancestors, victim);
    }

    bool found = false;
    for (int i = 1; i <= n; ++i) {
        if (!isHuman[i]) {
            printf("%d ", i);
            found = true;
        }
    }

    if (!found)
        printf("0\n");
    else
        printf("\n");
}

int inputRelation(Relation *descendants[], Relation *ancestors[]) {
    int n;
    scanf("%d", &n);
    getchar();

    char line[LINE_BUF_LEN];
    scanf("%[^\n]", line);
    getchar();
    int child, parent;
    while (line[0] != 'B') {
        sscanf(line, "%d %d", &child, &parent);

        addRelation(descendants, parent, child);
        addRelation(ancestors, child, parent);

        scanf("%[^\n]", line);
        getchar();
    }

    return n;
}

void addRelation(Relation *relation[], int id, int newRelation) {
    Relation *r = new Relation();
    r->id = newRelation;
    r->next = relation[id];
    relation[id] = r;
}

void dfs(Relation *relation[], int id) {
    isHuman[id] = true;

    Relation *r = relation[id];
    while (r != NULL) {
        dfs(relation, r->id);
        r = r->next;
    }
}