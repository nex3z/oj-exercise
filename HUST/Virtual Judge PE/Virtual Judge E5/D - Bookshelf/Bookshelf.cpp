#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define ERROR 0.000001

double cal(int h, int H, double angle);
void solveE5d_Bookshelf();

int main() {
    solveE5d_Bookshelf();
    return 0;
}

void solveE5d_Bookshelf() {
    int h, H, l;
    scanf("%d %d %d", &h, &H, &l);
    if (h >= H) {
        printf("0\n");
        return;
    }

    double left = PI / 2.0, right = 0, mid = (left + right) / 2.0, result, c;

    while (left - right > ERROR) {
        c = cal(h, H, mid);
        if (c > 0) {
            right = mid;
        }
        else {
            left = mid;
        }
        mid = (left + right) / 2.0;
    }

    result = H / 2.0 * cos(mid) - h / tan(mid);
    printf("%.10lf\n", result > 0 ? result : 0);
}

double cal(int h, int H, double angle) {
    double c = cos(angle), s = sin(angle);
    return (-1 * s * H / 2.0 + h / (s*s));
}