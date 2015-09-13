#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

const int MAX_DIGITS_NUM = 30;
const int MAX_TRIAL_NUM = 1000001;
const int ADD_DIGIT_FLAG = -1;

struct Digit {
    int digit, mod, pre;
};

void solveE6g_OneTwoOneTwo2();
void setDigit(Digit &d, int digit, int mod, int pre);

int main() {
    solveE6g_OneTwoOneTwo2();
}

Digit queue[MAX_TRIAL_NUM];
bool calculated[MAX_TRIAL_NUM];
void solveE6g_OneTwoOneTwo2() {
    int n;
    scanf("%d", &n);
    
    int front = 0, rear = 0;
    setDigit(queue[front++], 1, 1 % n, -1);
    calculated[1 % n] = true;
    
    setDigit(queue[front++], 2, 2 % n, -1);
    calculated[2 % n] = true;
    
    setDigit(queue[front++], ADD_DIGIT_FLAG, -1, -1);
    
    bool found = false;
    int digitCnt = 1, lastDigitIdx;
    while (rear < front) {
        Digit curr = queue[rear++];
        if (curr.digit == ADD_DIGIT_FLAG) {
            if (front == rear) {
                break;
            }
            else {
                setDigit(queue[front++], ADD_DIGIT_FLAG, -1, -1);
                if (++digitCnt > MAX_DIGITS_NUM) {
                    break;
                }
                else {
                    continue;
                }
            }
        } else if (curr.mod == 0) {
            found = true;
            lastDigitIdx = rear - 1;
            break;
        }
        
        int newMod = (curr.mod * 10 + 1) % n;
        if (!calculated[newMod]) {
            setDigit(queue[front++], 1, newMod, rear - 1);
            calculated[newMod] = true;
        }
        
        newMod = (curr.mod * 10 + 2) % n;
        if (!calculated[newMod]) {
            setDigit(queue[front++], 2, newMod, rear - 1);
            calculated[newMod] = true;
        }
    }
    
    if (found) {
        int result[MAX_DIGITS_NUM + 1], cnt = 0;
        for (int i = lastDigitIdx; i != -1; i = queue[i].pre, ++cnt) {
            result[cnt] = queue[i].digit;
        }
        for (int i = cnt - 1; i >= 0; --i) {
            printf("%d", result[i]);
        }
        printf("\n");
    }
    else {
        printf("Impossible\n");
    }
    
}

void setDigit(Digit &d, int digit, int mod, int pre) {
    d.digit = digit;
    d.mod = mod;
    d.pre = pre;
}