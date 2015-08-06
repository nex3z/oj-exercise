#include <stdio.h>
#include <stdlib.h>

#define MAX_EXAM_NUM 100000
#define REVIEW_NEEDED 0
#define EXAM_START 1
#define EXAM_DURATION 2

typedef int Schedule[MAX_EXAM_NUM][3];

bool solveE4c_Exam();
int inputSchedule(Schedule schedule);
int cmp(const void *a, const void *b);

int main() {
    int testcaseNum;
    scanf("%d", &testcaseNum);

    bool canPass;
    for (int i = 1; i <= testcaseNum; ++i) {
        canPass = solveE4c_Exam();
        printf("Case #%d: ", i);
        if (canPass)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}

Schedule schedule;
bool solveE4c_Exam() {
    int examNum = inputSchedule(schedule);
    qsort(schedule, examNum, sizeof(int)*3, cmp);

    int i;
    for (i = 0; i < examNum; ++i) {
        if (schedule[i][REVIEW_NEEDED] > schedule[i][EXAM_START]) {
            return false;
        } else {
            schedule[i + 1][REVIEW_NEEDED] += schedule[i][REVIEW_NEEDED] + schedule[i][EXAM_DURATION];
        }
    }

    return schedule[i][REVIEW_NEEDED] > schedule[i][EXAM_START];
}

int inputSchedule(Schedule schedule) {
    int examNum;
    scanf("%d", &examNum);

    for (int i = 0; i < examNum; ++i) {
        scanf("%d %d %d", &schedule[i][REVIEW_NEEDED], &schedule[i][EXAM_START], &schedule[i][EXAM_DURATION]);
    }

    return examNum;
}

int cmp(const void *a, const void *b) {
    return *((int *)a + EXAM_START) - *((int *)b + EXAM_START);
}