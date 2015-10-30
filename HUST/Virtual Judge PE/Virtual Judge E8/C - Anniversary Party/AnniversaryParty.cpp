#include <cstdio>

#define MAX_N 6001

typedef struct EmployeeRecord {
    int id;
    struct EmployeeRecord *next;
} Employee;

void solvePE8c_AnniversaryParty();
int input(Employee *employees[], int rating[], int n);
void dfs(int id);
int max(int a, int b);

int main() {
    // freopen("test.txt", "r", stdin);
    solvePE8c_AnniversaryParty();
    return 0;
}

Employee *employees[MAX_N];
int rating[MAX_N], maxRating[MAX_N][2];
void solvePE8c_AnniversaryParty() {
    int n;
    scanf("%d", &n);
    int president = input(employees, rating, n);

    dfs(president);

    int result = max(maxRating[president][0], maxRating[president][1]);
    printf("%d\n", result);
}

void dfs(int id) {
    maxRating[id][0] = 0;
    maxRating[id][1] = rating[id];

    if (employees[id] != NULL) {
        maxRating[id][0] = 0;
        maxRating[id][1] = rating[id];
        Employee *e = employees[id];
        while (e != NULL) {
            dfs(e->id);
            maxRating[id][0] += max(maxRating[e->id][1], maxRating[e->id][0]);
            maxRating[id][1] += maxRating[e->id][0];
            e = e->next;
        }
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

bool isEmployee[MAX_N];
int input(Employee *employees[], int rating[], int n) {
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &rating[i]);
    }

    int employee, superv;
    scanf("%d %d", &employee, &superv);
    while (employee != 0) {
        Employee *e = new Employee();
        e->id = employee;
        e->next = employees[superv];
        employees[superv] = e;
        isEmployee[employee] = true;

        scanf("%d %d", &employee, &superv);
    }

    for (int i = 1; i <= n; ++i) {
        if (!isEmployee[i]) {
            return i;
        }
    }

    return -1;
}