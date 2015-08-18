#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_STONE_NUM 20
#define MAX_PILE_WEIGHT 100000
#define PACK_SIZE MAX_PILE_WEIGHT * MAX_STONE_NUM

void solveE2d();
int inputpiles(int piles[], int n);
void buildPack(int pack[], int capacity, int piles[], int n);

int main() {
    solveE2d();
    return 0;
}

int pack[PACK_SIZE];
void solveE2d() {
    int n, piles[MAX_STONE_NUM], totalWeight, result;

    scanf("%d", &n);
    totalWeight = inputpiles(piles, n);
    buildPack(pack, totalWeight / 2, piles, n);
    result = totalWeight - pack[totalWeight / 2] * 2;
    printf("%d\n", result);
}

int inputpiles(int piles[], int n) {
    int i, totalWeight;

    for (i = 0, totalWeight = 0; i < n; ++i) {
        scanf("%d", &piles[i]);
        totalWeight += piles[i];
    }
    return totalWeight;
}

void buildPack(int pack[], int capacity, int piles[], int n) {
    int i, j, weightWithPileI;
    
    memset(pack, 0, sizeof(int) * PACK_SIZE);

    for (i = 0; i < n; ++i) {
        for (j = capacity; j >= piles[i]; --j) {
            weightWithPileI = pack[j - piles[i]] + piles[i];
            if (weightWithPileI > pack[j]) {
                pack[j] = weightWithPileI;
            }
        }
    }
}