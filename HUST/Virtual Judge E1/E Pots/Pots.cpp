#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define MAX_VOLUME 100
#define OP_FILL_1 1
#define OP_FILL_2 2
#define OP_DROP_1 3
#define OP_DROP_2 4
#define OP_POUR_1_2 5
#define OP_POUR_2_1 6
#define NOT_PRESENTED 0
#define PRESENTED 1

typedef unsigned char History[MAX_VOLUME + 1][MAX_VOLUME + 1];

typedef struct StatusRecord {
    int a;
    int b;
    int operation;
    int step;
    int lastId;
} Status;

void solveE1e();
int findSolution(int volA, int volB, int goal, Status status[]);
void initHistory(History history);
void setStatus(Status *current, int a, int b, int operation, int step, int lastId);
void printSolution(Status status[], int last);

int main() {
    solveE1e();
    // system("pause");
    return 0;
}

Status status[(MAX_VOLUME + 1) * (MAX_VOLUME + 1)];
void solveE1e() {
    int volA, volB, goal, last;

    scanf("%d %d %d", &volA, &volB, &goal);
    if (goal == 0) {
        printf("0\n");
    } else {
        last = findSolution(volA, volB, goal, status);
        if (last == -1) {
            printf("impossible\n");
        } else {
            printSolution(status, last);
        }
    }
}

History history;
int findSolution(int volA, int volB, int goal, Status status[]) {
    int front = 0, rear = 0;
    Status current, next;

    initHistory(history);
    setStatus(&status[rear++], 0, 0, 0, 0, -1);
    history[0][0] = PRESENTED;

    while (front < rear) {
        current = status[front++];
        
        if (current.a == goal || current.b == goal) {
            return front - 1;
        }

        // OP_FILL_1
        setStatus(&next, volA, current.b, OP_FILL_1, current.step + 1, front - 1);
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }

        // OP_FILL_2
        setStatus(&next, current.a, volB, OP_FILL_2, current.step + 1, front - 1);
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }

        // OP_DROP_1
        setStatus(&next, 0, current.b, OP_DROP_1, current.step + 1, front - 1);
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }

        // OP_DROP_2
        setStatus(&next, current.a, 0, OP_DROP_2, current.step + 1, front - 1);
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }

        // OP_POUR_1_2
        if (current.a + current.b <= volB) {
            setStatus(&next, 0, current.a + current.b, OP_POUR_1_2, current.step + 1, front - 1);
        } else {
            setStatus(&next, current.a + current.b - volB, volB, OP_POUR_1_2, current.step + 1, front - 1);
        }
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }

        // OP_POUR_2_1
        if (current.a + current.b <= volA) {
            setStatus(&next, current.a + current.b, 0, OP_POUR_2_1, current.step + 1, front - 1);
        }
        else {
            setStatus(&next, volA, current.a + current.b - volA, OP_POUR_2_1, current.step + 1, front - 1);
        }
        if (history[next.a][next.b] == NOT_PRESENTED) {
            status[rear++] = next;
            history[next.a][next.b] = PRESENTED;
        }
    }

    return -1;
}

void initHistory(History history) {
    int i, j;
    for (i = 0; i <= MAX_VOLUME; ++i) {
        for (j = 0; j <= MAX_VOLUME; ++j) {
            history[i][j] = NOT_PRESENTED;
        }
    }
}

void setStatus(Status *current, int a, int b, int operation, int step, int lastId) {
    current->a = a;
    current->b = b;
    current->operation = operation;
    current->step = step;
    current->lastId = lastId;
}

unsigned char opSeq[(MAX_VOLUME + 1) * (MAX_VOLUME + 1)];
void printSolution(Status status[], int last) {
    int step, statusId, op, i;
    
    step = status[last].step;
    printf("%d\n", step);
    statusId = last;
    while (step--) {
        op = status[statusId].operation;
        opSeq[step] = op;
        statusId = status[statusId].lastId;
    }

    for (i = 0; i < status[last].step; ++i) {
        op = opSeq[i];
        switch (op) {
        case OP_FILL_1:
            printf("FILL(1)\n"); break;
        case OP_FILL_2:
            printf("FILL(2)\n"); break;
        case OP_DROP_1:
            printf("DROP(1)\n"); break;
        case OP_DROP_2:
            printf("DROP(2)\n"); break;
        case OP_POUR_1_2:
            printf("POUR(1,2)\n"); break;
        case OP_POUR_2_1:
            printf("POUR(2,1)\n"); break;
        default:
            break;
        }

    }

}
