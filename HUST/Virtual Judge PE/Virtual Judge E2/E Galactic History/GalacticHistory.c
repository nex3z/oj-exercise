#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 40010
#define MAX_L 40010

#define STATUS_NONE 0
#define STATUS_A_IS_ROOT_OF_B 1
#define STATUS_B_IS_ROOT_OF_A 2
#define STATUS_NOT_FOUND 3
#define STATUS_FOUND_A 4
#define STATUS_FOUND_B 5

struct MilestoneRecord;
typedef struct MilestoneRecord Milestone;
typedef Milestone *PtrToMilestone;
struct QueryRecord;
typedef struct QueryRecord Query;
typedef Query *PtrToQuery;

void solveE2e();
int inputMilestones(Milestone milestone[], int n);
void printMilestone(Milestone milestone[], int root);
void inputQueries(int aList[], int bList[], int statusList[], Query query[], int l);
void performQuery(int root);

struct MilestoneRecord{
    int childId;
    PtrToMilestone next;
};

struct QueryRecord{
    int queryId;
    PtrToQuery next;
};

int main() {
    solveE2e();
    return 0;
}

Milestone milestone[MAX_N];
Query query[MAX_L];
int aList[MAX_L], bList[MAX_L], statusList[MAX_L];
void solveE2e() {
    int n, root, l, i;

    scanf("%d", &n);
    root = inputMilestones(milestone, n);

    scanf("%d", &l);
    inputQueries(aList, bList, statusList, query, l);
    //printMilestone(milestone, root);

    performQuery(root);

    for (i = 0; i < l; ++i) {
        printf("%d ", statusList[i]);
    }
    printf("\n");
}

int inputMilestones(Milestone milestone[], int n) {
    int root, i, childId, parentId;
    PtrToMilestone tmp;

    for (i = 0; i < n; ++i) {
        scanf("%d %d", &childId, &parentId);
        if (parentId == -1) {
            root = childId;
        } else {
            tmp = malloc(sizeof(Milestone));
            tmp->childId = childId;
            tmp->next = milestone[parentId].next;
            milestone[parentId].next = tmp;
        }
    }

    return root;
}

void inputQueries(int aList[], int bList[], int statusList[], Query query[], int l) {
    int i, a, b;
    PtrToQuery tmp;
    
    for (i = 0; i < l; ++i) {
        scanf("%d %d", &a, &b);
        aList[i] = a;
        bList[i] = b;
        statusList[i] = STATUS_NOT_FOUND;

        tmp = malloc(sizeof(Query));
        tmp->queryId = i;
        tmp->next = query[a].next;
        query[a].next = tmp;

        tmp = malloc(sizeof(Query));
        tmp->queryId = i;
        tmp->next = query[b].next;
        query[b].next = tmp;
    }
}

void performQuery(int root) {
    int queryId, a, b;
    PtrToQuery relatedQuery;
    PtrToMilestone child;

    relatedQuery = query[root].next;
    while (relatedQuery != NULL) {
        queryId = relatedQuery->queryId;
        a = aList[queryId];
        b = bList[queryId];
        if (statusList[queryId] == STATUS_NOT_FOUND) {
            if (a == root)
                statusList[queryId] = STATUS_FOUND_A;
            else if (b == root)
                statusList[queryId] = STATUS_FOUND_B;
        }
        else if (statusList[queryId] == STATUS_FOUND_A) {
            if (b == root)
                statusList[queryId] = STATUS_A_IS_ROOT_OF_B;
        }
        else if (statusList[queryId] == STATUS_FOUND_B) {
            if (a == root)
                statusList[queryId] = STATUS_B_IS_ROOT_OF_A;
        }
        relatedQuery = relatedQuery->next;
    }

    child = milestone[root].next;
    while (child != NULL) {
        performQuery(child->childId);
        child = child->next;
    }

    relatedQuery = query[root].next;
    while (relatedQuery != NULL) {
        queryId = relatedQuery->queryId;
        if (statusList[queryId] == STATUS_FOUND_A || statusList[queryId] == STATUS_FOUND_B)
            statusList[queryId] = STATUS_NONE;
        relatedQuery = relatedQuery->next;
    }
}

void printMilestone(Milestone milestone[], int root) {
    int queryId;
    PtrToMilestone child;
    PtrToQuery relatedQuery;

    printf("Milestone %d: ", root);
    child = milestone[root].next;
    while (child != NULL) {
        printf("%d ", child->childId);
        child = child->next;
    }
    printf("\n");

    printf("Query: ");
    relatedQuery = query[root].next;
    while (relatedQuery != NULL) {
        queryId = relatedQuery->queryId;
        printf("(%d: %d %d %d) ", queryId, aList[queryId], bList[queryId], statusList[queryId]);
        relatedQuery = relatedQuery->next;
    }
    printf("\n\n");

    child = milestone[root].next;
    while (child != NULL) {
        printMilestone(milestone, child->childId);
        child = child->next;
    }
}