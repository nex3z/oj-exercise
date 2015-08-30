#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAM_NUM 100
#define MAX_NAME_LEN 20
#define TEAM_MEMBER_NUM 3

#define DEBUG 0

typedef char TeamList[MAX_TEAM_NUM][TEAM_MEMBER_NUM][MAX_NAME_LEN + 1];
typedef char MemberList[MAX_TEAM_NUM * TEAM_MEMBER_NUM][MAX_NAME_LEN + 1];
typedef char Connection[MAX_TEAM_NUM * TEAM_MEMBER_NUM][MAX_TEAM_NUM * TEAM_MEMBER_NUM];

void solveE1b();
void inputTeamInfo(TeamList teamList, int *teamNum, MemberList memberList, int *memberNum);
int addMember(const char *name, MemberList memberList, int memberListLen);
void buildConnection(TeamList teamList, int teamListLen, int memberNum, Connection conn);
int getMemberId(const char *name, MemberList memberList, int memberNum);
void computeDist(int startId, Connection conn, int memberNum, int *dist);
void printMemberDist(MemberList memberList, int *dist, int memberNum);

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;
int isEmpty(Queue q);
Queue createQueue(int maxElements);
void disposeQueue(Queue q);
void enqueue(ElementType x, Queue q);
ElementType frontAndDequeue(Queue q);

struct QueueRecord{
    int capacity;
    int front;
    int rear;
    int size;
    ElementType *array;
};

TeamList teamList;
MemberList memberList;
Connection connection;
int dist[MAX_TEAM_NUM * TEAM_MEMBER_NUM] = {-1};

int main(void) {
#if DEBUG == 2
    freopen("test.txt", "r", stdin);
#endif // DEBUG
    solveE1b();
    return 0;
}

void solveE1b() {
    int teamNum = 0, memberNum = 0, isenbaevId = 0;
    
    inputTeamInfo(teamList, &teamNum, memberList, &memberNum);
    buildConnection(teamList, teamNum, memberNum, connection);
    
    memset(dist, -1, sizeof(int) * MAX_TEAM_NUM * TEAM_MEMBER_NUM);
    isenbaevId = getMemberId("Isenbaev", memberList, memberNum);
    if (isenbaevId != -1) {
        computeDist(isenbaevId, connection, memberNum, dist);
    }
    printMemberDist(memberList, dist, memberNum);
}

void inputTeamInfo(TeamList teamList, int *teamNum, MemberList memberList, int *memberNum) {
    int i = 0, j = 0, memberListLen = 0;
    
    scanf("%d", teamNum);
    for (i = 0; i < *teamNum; ++i) {
        for (j = 0; j < TEAM_MEMBER_NUM; ++j) {
            scanf("%s", teamList[i][j]);
            memberListLen += addMember(teamList[i][j], memberList, memberListLen);
        }
    }
    
    *memberNum = memberListLen;
}

int addMember(const char *name, MemberList memberList, int memberListLen) {
    int i = 0, j = 0, cmp = 0;
    
    for (i = 0; i < memberListLen; ++i) {
        cmp = strcmp(name, memberList[i]);
        if (cmp < 0) {
            for (j = memberListLen; j >= i; --j) {
                strcpy(memberList[j], memberList[j - 1]);
            }
            strcpy(memberList[i], name);
            return 1;
        } else if(cmp == 0) {
            return 0;
        }
    }
    strcpy(memberList[i], name);
    return 1;
}

void buildConnection(TeamList teamList, int teamListLen, int memberNum, Connection conn) {
    int i = 0, j = 0, k = 0, id[TEAM_MEMBER_NUM] = {0};
    
    for (i = 0; i < teamListLen; ++i) {
        for (j = 0; j < TEAM_MEMBER_NUM; ++j)
            id[j] = getMemberId(teamList[i][j], memberList, memberNum);
        
        for (j = 0; j < TEAM_MEMBER_NUM; ++j) {
            for (k = 0; k < TEAM_MEMBER_NUM; ++k) {
                if (j == k) {
                    conn[id[j]][id[k]] = 0;
                } else {
                    conn[id[j]][id[k]] = 1;
                }
            }
        }
    }
}

int getMemberId(const char *name, MemberList memberList, int memberNum) {
    int i = 0;
    
    for (i = 0; i < memberNum; ++i) {
        if (strcmp(name, memberList[i]) == 0)
            return i;
    }
    return -1;
}

void computeDist(int startId, Connection conn, int memberNum, int *dist) {
    int i = 0, currentId = 0, distCnt = 0;
    char visited[MAX_TEAM_NUM * TEAM_MEMBER_NUM] = {0};
    Queue q;
    
    for (i = 0; i < memberNum; ++i) {
        dist[i] = -1;
    }
    q = createQueue(MAX_TEAM_NUM * TEAM_MEMBER_NUM);
    
    dist[startId] = distCnt;
    visited[startId] = 1;
    enqueue(startId, q);
    enqueue(-1, q);
    ++distCnt;
    
    while (!isEmpty(q)) {
        currentId = frontAndDequeue(q);
        if (currentId == -1) {
            if (isEmpty(q)) {
                break;
            } else {
                ++distCnt;
                enqueue(-1, q);
                continue;
            }
        }
        for (i = 0; i < memberNum; ++i) {
            if (conn[currentId][i] == 1 && visited[i] == 0) {
                dist[i] = distCnt;
                visited[i] = 1;
                enqueue(i, q);
            }
        }
    }
    disposeQueue(q);
}

void printMemberDist(MemberList memberList, int *dist, int memberNum) {
    int i = 0;
    
    for (i = 0; i < memberNum; ++i) {
        printf("%s ", memberList[i]);
        if (dist[i] == -1) {
            printf("undefined\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

void makeEmpty(Queue q) {
    q->size = 0;
    q->front = 1;
    q->rear = 0;
}

Queue createQueue(int maxElements) {
    Queue q;
    
    q = malloc(sizeof(struct QueueRecord));
    q->array = malloc(sizeof(ElementType)* maxElements);
    q->capacity = maxElements;
    makeEmpty(q);
    
    return q;
}

int isEmpty(Queue q) {
    return q->size == 0;
}

int isFull(Queue q) {
    return q->size == q->capacity;
}

void disposeQueue(Queue q) {
    free(q->array);
    free(q);
}

static int succ(int value, Queue q) {
    if (++value == q->capacity) {
        value = 0;
    }
    return value;
}

void enqueue(ElementType x, Queue q) {
    if (isFull(q)) {
        printf("Error: Full queue.\n");
    }
    else {
        q->size++;
        q->rear = succ(q->rear, q);
        q->array[q->rear] = x;
    }
}

ElementType front(Queue q) {
    return q->array[q->front];
}

void dequeue(Queue q) {
    q->front = succ(q->front, q);
    q->size--;
}

ElementType frontAndDequeue(Queue q) {
    ElementType e;
    
    e = front(q);
    dequeue(q);
    return e;
}
