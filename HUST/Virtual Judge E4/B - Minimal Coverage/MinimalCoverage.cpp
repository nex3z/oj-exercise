// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SEGMENT_NUM 99999

typedef struct LineRecord {
	int start, end;
} Line;

void solveE4aMinimalCoverage();
int inputSchedule(Line line[]);
int cmp(const void *a, const void *b);

int main() {
	solveE4aMinimalCoverage();
	return 0;
}


Line line[MAX_SEGMENT_NUM];
void solveE4aMinimalCoverage() {
    int m;
    scanf("%d", &m);

	int n = inputSchedule(line);
	qsort(line, n, sizeof(Line), cmp);

    int lastStart = 0, lastEnd = m, cnt = 0;
    int candLineId = 0, candLineEnd = -1;
    int selection[MAX_SEGMENT_NUM];
	for (int i = 0; i < n; ++i) {
        if (line[i].start <= lastStart) {
            if (line[i].end > candLineEnd) {
                candLineEnd = line[i].end;
                candLineId = i;
                if (candLineEnd >= m) {
                    selection[cnt++] = candLineId;
                    break;
                }
            }
        } else {
            lastStart = candLineEnd;
            selection[cnt++] = candLineId;

            if (line[i].start <= lastStart) {
                if (line[i].end > candLineEnd) {
                    candLineEnd = line[i].end;
                    candLineId = i;
                    if (candLineEnd >= m) {
                        selection[cnt++] = candLineId;
                        break;
                    }
                }
            }
        }
	}

    if (candLineEnd < m) {
        printf("No solution\n");
    } else {
        printf("%d\n", cnt);
        for (int i = 0; i < cnt; ++i) {
            printf("%d %d\n", line[selection[i]].start, line[selection[i]].end);
        }
    }
}

int inputSchedule(Line line[]) {
	int n = 0, start, end;

    scanf("%d %d", &start, &end);
    while (start != 0 || end != 0) {
        line[n].start = start;
        line[n].end = end;
        ++n;
        scanf("%d %d", &start, &end);
    }
	return n;
}

int cmp(const void *a, const void *b) {
	if ((*(Line *)a).start != (*(Line *)b).start) {
        return (*(Line *)a).start - (*(Line *)b).start;
	} else {
        return (*(Line *)b).end - (*(Line *)a).end;
	}
}