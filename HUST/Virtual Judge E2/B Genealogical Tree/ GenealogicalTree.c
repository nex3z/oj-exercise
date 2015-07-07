#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define DELETED 255

typedef char Graph[MAX_N + 1][MAX_N + 1];

void solveE2b();
int inputGraph(Graph g, unsigned char degree[]);
void initDegree(unsigned char degree[], int n);
void getSeq(int n, Graph g, unsigned char degree[], unsigned char seq[]);
void printArrayRev(unsigned char array[], int len);
void printArray(unsigned char array[], int len);
void printGraph(Graph g, int width);

int main() {
    solveE2b();
    return 0;
}

Graph g;
unsigned char degree[MAX_N + 1], seq[MAX_N + 1];;
void solveE2b() {
    int n;
    n = inputGraph(g, degree);
    //printGraph(g, n);
    //printf("degree = ");
    //printArray(degree, n);
    getSeq(n, g, degree, seq);
    printArray(seq, n);
}

int inputGraph(Graph g, unsigned char degree[]) {
    int n, i, j, child;
    
    scanf("%d", &n);
    initDegree(degree, n);
    
    for (i = 1; i <= n; ++i) {
        j = 0;
        scanf("%d", &child);
        while (child != 0) {
            g[i][j++] = child;
            ++degree[i];
            scanf("%d", &child);
        }
    }
    
    return n;
}

void initDegree(unsigned char degree[], int n) {
    int i;
    
    for (i = 1; i <= n; ++i) {
        degree[i] = 0;
    }
}


void getSeq(int n, Graph g, unsigned char degree[], unsigned char seq[]) {
    int count = n, i, j;
    unsigned char removed = 0;
    
    while (count) {
        for (i = 1; i <= n; ++i) {
            if (degree[i] == 0) {
                removed = i;
                seq[count--] = i;
                degree[i] = DELETED;
                break;
            }
        }
        //printf("count = %d, removed = %d\n", count, removed);
        //printf("degree = "); printArray(degree, n);
        //printf("seq = "); printArray(seq, n);
        
        for (i = 1; i <= n; ++i) {
            if (degree[i] == DELETED)
                continue;
            
            for (j = 0; j < n; ++j) {
                if (g[i][j] == removed) {
                    g[i][j] = DELETED;
                    --degree[i];
                    break;
                }
            }
        }
        //printGraph(g, n);
    }
}

void printArrayRev(unsigned char array[], int len) {
    while(len--) {
        printf("%d ", array[len]);
    }
    printf("\n");
}

void printArray(unsigned char array[], int len) {
    int i;
    
    for (i = 1; i <= len; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printGraph(Graph g, int width) {
    int i, j;
    
    for (i = 1; i <= width; ++i) {
        for (j = 0; j < width; ++j) {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
}