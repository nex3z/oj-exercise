#include <stdio.h>
#include <stdlib.h>

#define MAX_CITY_NUM 100001

typedef int RoadList[MAX_CITY_NUM][2];
typedef struct CityRecord {
    int cityId, roadId;
    struct CityRecord *next;
} City;

void solveE4g_Roadworks();
void inputRoads(RoadList roadList, int m, City *cities[], int degree[]);
void addCity(City *cities[], int id, int newCityId, int newRoadId);
void removeCity(City *cities[], int fromId, int deleteId);
void printCities(City *cities[], int n);
int cmp(const void *a, const void *b);

int main() {
    solveE4g_Roadworks();
    return 0;
}

RoadList roadList;
City *cities[MAX_CITY_NUM];
int removedRoadId[MAX_CITY_NUM], degree[MAX_CITY_NUM], oneDegreeQueue[MAX_CITY_NUM];
bool isCityProtected[MAX_CITY_NUM];
void solveE4g_Roadworks() {
    int n, m, removedRoadCnt = 0;
    scanf("%d %d", &n, &m);

    inputRoads(roadList, m, cities, degree);
    // printCities(cities, n);

    int front = 0, rear = 0;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            oneDegreeQueue[rear++] = i;
        }
    }

    while (front != rear) {
        int currCityId = oneDegreeQueue[front++];
        if (isCityProtected[currCityId]) {
            continue;
        }

        City *otherCity = cities[currCityId];
        if (otherCity == NULL) {
            continue;
        }
        removedRoadId[removedRoadCnt++] = otherCity->roadId;
        int otherCityId = otherCity->cityId;
        degree[currCityId] = -1;
        isCityProtected[currCityId] = true;
        degree[otherCityId] = -1;
        isCityProtected[otherCityId] = true;

        City *connectedCity = cities[otherCityId];
        while (connectedCity != NULL) {
            int connectedCityId = connectedCity->cityId;
            if (connectedCityId == currCityId) {
                connectedCity = connectedCity->next;
                continue;
            }

            removeCity(cities, connectedCityId, otherCityId);
            --degree[connectedCityId];
            if (degree[connectedCityId] == 1) {
                oneDegreeQueue[rear++] = connectedCityId;
            }
            connectedCity = connectedCity->next;
        }

        // printf("Removed %d %d\n", currCityId, otherCityId);
        // printCities(cities, n);
        // printf("\n");
    }


    printf("%d\n", removedRoadCnt);
    qsort(removedRoadId, removedRoadCnt, sizeof(int), cmp);
    for (int i = 0; i < removedRoadCnt; ++i) {
        printf("%d %d\n", roadList[removedRoadId[i]][0], roadList[removedRoadId[i]][1]);
    }

}

void inputRoads(RoadList roadList, int m, City *cities[], int degree[]) {
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &roadList[i][0], &roadList[i][1]);
        addCity(cities, roadList[i][0], roadList[i][1], i);
        addCity(cities, roadList[i][1], roadList[i][0], i);
        ++degree[roadList[i][0]];
        ++degree[roadList[i][1]];
    }
}

void addCity(City *cities[], int id, int newCityId, int newRoadId) {
    City *newCity = new City();
    newCity->cityId = newCityId;
    newCity->roadId = newRoadId;
    newCity->next = cities[id];

    cities[id] = newCity;
}

void removeCity(City *cities[], int fromId, int deleteId) {

    if (cities[fromId]->cityId == deleteId) {
        cities[fromId] = cities[fromId]->next;
    } else {
        City *city = cities[fromId];

        while (city->next != NULL) {
            if (city->next->cityId == deleteId) {
                city->next = city->next->next;
                return;
            }
            city = city->next;
        }
    }
}

int cmp(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void printCities(City *cities[], int n) {
    for (int i = 1; i <= n; ++i) {
        printf("%2d: ", i);
        City *c = cities[i];
        while (c != NULL) {
            printf("(%2d, %2d) ", c->cityId, c->roadId);
            c = c->next;
        }
        printf("\n");
    }

}