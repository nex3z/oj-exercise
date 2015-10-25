#include <cstdio>
 
const int MAX_N = 1001;
const int NOT_LEAF = -2;
const int PLAYER_1 = 1;
const int PLAYER_2 = 2;
 
typedef struct NodeRecord {
    int id, value;
    struct NodeRecord *next;
} Node;
 
void solve();
int minimax(Node *node, int player);
int input(Node graph[]);
Node *newNode(int id, int value, Node *next);
void setNode(Node *node, int id, int value, Node *next);
int max(int a, int b);
int min(int a, int b);
 
int main() {
    // freopen("test.txt", "r", stdin);
    solve();
    return 0;
}
 
Node graph[MAX_N];
void solve() {
    int n = input(graph);
    int score = minimax(&graph[1], PLAYER_1);
 
    if (score == 1) {
        printf("+1\n");
    }
    else if (score == -1) {
        printf("-1\n");
    }
    else {
        printf("0\n");
    }
}
 
int minimax(Node *node, int player) {
    if (node->value != NOT_LEAF) {
        return node->value;
    }
 
    int score;
    Node *curr = graph[node->id].next;
    if (player == PLAYER_1) {
        score = -2;
        while (curr != NULL) {
            score = max(score, minimax(curr, PLAYER_2));
            if (score == 1) break;
            curr = curr->next;
        }
    }
    else {
        score = 2;
        while (curr != NULL) {
            score = min(score, minimax(curr, PLAYER_1));
            if (score == -1) break;
            curr = curr->next;
        }
    }
    return score;
}
 
int input(Node graph[]) {
    int n, parent, value;
    char type;
 
    setNode(&graph[1], 1, NOT_LEAF, NULL);
    scanf("%d", &n);
 
    for (int i = 2; i <= n; ++i) {
        getchar();
        scanf("%c %d", &type, &parent);
        if (type == 'L') {
            scanf("%d", &value);
        }
        else {
            value = NOT_LEAF;
        }
        setNode(&graph[i], i, value, NULL);
        Node *node = newNode(i, value, graph[parent].next);
        graph[parent].next = node;
    }
    return n;
}
 
Node *newNode(int id, int value, Node *next) {
    Node *node = new Node();
    node->id = id;
    node->value = value;
    node->next = next;
    return node;
}
 
void setNode(Node *node, int id, int value, Node *next) {
    node->id = id;
    node->value = value;
    node->next = next;
}
 
int max(int a, int b) {
    return a > b ? a : b;
}
 
int min(int a, int b) {
    return a > b ? b : a;
}