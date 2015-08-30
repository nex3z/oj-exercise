#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_REPORT_NUM 100001

typedef struct ScheduleRecord {
    int start, end;
} Schedule;

void solveE4aScientificConference();
int inputSchedule(Schedule schedule[]);
int cmp(const void *a, const void *b);

int main() {
    solveE4aScientificConference();
    return 0;
}


Schedule schedule[MAX_REPORT_NUM];
void solveE4aScientificConference() {
    int n = inputSchedule(schedule);
    qsort(schedule, n, sizeof(Schedule), cmp);

    int lastEnd = schedule[0].end;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (schedule[i].start > lastEnd) {
            lastEnd = schedule[i].end;
            ++cnt;
        }
    }

    printf("%d\n", cnt);
}

int inputSchedule(Schedule schedule[]) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &schedule[i].start, &schedule[i].end);
    }

    return n;
}

int cmp(const void *a, const void *b) {
    return (*(Schedule *)a).end - (*(Schedule *)b).end;
}