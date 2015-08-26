#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <queue>

using namespace std;

#define MAX_ROAD_NUM 10001
#define MAX_COST_TIME 0x1FFFFFFF
#define ERROR 0.0000001

typedef int CrossIdType;
typedef int SpeedType;

typedef struct RoadRecord {
	CrossIdType a, b;
	double s;
	double l;
	int id, next;
} Road;

void solveE5e_RoadToInvestor();
void inputRoads(Road roads[], int num);
double getMinTime(Road roads[], int roadNum, int destCrossId, double overspeed);

int main() {
	solveE5e_RoadToInvestor();
	return 0;
}

Road roads[MAX_ROAD_NUM];
double costTime[MAX_ROAD_NUM];
int pre[MAX_ROAD_NUM], selectedRoadIdPre[MAX_ROAD_NUM], selectedRoadId[MAX_ROAD_NUM], index[MAX_ROAD_NUM];
queue<int> q;
bool visited[MAX_ROAD_NUM];
void solveE5e_RoadToInvestor() {
	int n, m, timeLimit;
	scanf("%d %d", &n, &m);
	inputRoads(roads, m);
	scanf("%d", &timeLimit);
	getMinTime(roads, m, n, 20);

	double l = 0, r = 100000000, mid = (l + r) / 2.0;
	while (fabs(r - l) > ERROR) {
		if (getMinTime(roads, m, n, mid) <= timeLimit) {
			r = mid;
		}
		else {
			l = mid;
		}
		mid = (l + r) / 2.0;
	}

	int cnt = 0;
	for (int i = n; pre[i] != 0; i = pre[i]) {
		selectedRoadId[cnt++] = selectedRoadIdPre[i];
	}
	printf("%.6lf %d\n", mid, cnt);

	for (int i = cnt - 1; i >= 0; --i) {
		printf("%d ", selectedRoadId[i]);
	}
	printf("\n");

}

void inputRoads(Road roads[], int num) {
	for (int i = 0; i <= num; ++i) {
		index[i] = -1;
	}

	for (int i = 0; i < num; ++i) {
		scanf("%d %d %lf %lf", &roads[i].a, &roads[i].b, &roads[i].s, &roads[i].l);
		roads[i].id = i+1;
		roads[i].next = index[roads[i].a];
		index[roads[i].a] = i;
	}
}

double getMinTime(Road roads[], int roadNum, int destCrossId, double overspeed) {
	costTime[1] = 0;
	q.push(1);
	visited[1] = true;
	for (int i = 2; i <= destCrossId; ++i) {
		visited[i] = false;
		costTime[i] = MAX_COST_TIME;
	}

	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		visited[curr] = false;
		for (int i = index[curr]; ~i; i = roads[i].next)
		{
			int next = roads[i].b;
			double w = roads[i].l / (roads[i].s + overspeed);
			if (costTime[next]>costTime[curr] + w)
			{
				costTime[next] = costTime[curr] + w;
				pre[next] = curr;
				selectedRoadIdPre[next] = roads[i].id;

				if (!visited[next])
				{
					visited[next] = true;
					q.push(next);
				}
			}
		}
	}
	return costTime[destCrossId];
}