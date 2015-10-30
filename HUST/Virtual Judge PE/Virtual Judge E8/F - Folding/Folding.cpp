#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 110;
const int INF = 0x0fffffff;

typedef struct SequenceRecord {
    char str[MAX_LENGTH];
    int len, rep;
} Sequence;


void solveE8f_Folding();
void setSequence(Sequence *seq, const char *str, int len, int rep);
void combineSequence(Sequence a, Sequence b, Sequence *combined);
void build(Sequence oriSeq, Sequence *result);
void test();

int main() {
    // freopen("test.txt", "r", stdin);
    // test();
    solveE8f_Folding();
    return 0;
}

void test() {
    char input[MAX_LENGTH], input2[MAX_LENGTH];
    scanf("%s", input);
    scanf("%s", input2);
    Sequence seq, seq2;
    setSequence(&seq, input, strlen(input), 1);
    setSequence(&seq2, input2, strlen(input2), 1);
    Sequence b, c;
    combineSequence(seq, seq2, &c);
    build(c, &b);
    printf("%s, %d, %d\n", b.str, b.len, b.rep);
}

Sequence seq[MAX_LENGTH][MAX_LENGTH];
void solveE8f_Folding() {
    char input[MAX_LENGTH];
    scanf("%s", input);
    int len = strlen(input);

    for (int i = 0; i < len; ++i) {
        char str[2] = { input[i], '\0' };
        setSequence(&seq[i][i], str, 1, 1);
    }

    for (int subSeqLen = 1; subSeqLen < len; ++subSeqLen) {
        for (int start = 0; start < len - subSeqLen; ++start) {
            int end = start + subSeqLen;
            Sequence combine;
            combineSequence(seq[start][start], seq[start + 1][end], &combine);
            for (int mid = start + 1; mid < end; ++mid) {
                Sequence tmp;
                combineSequence(seq[start][mid], seq[mid + 1][end], &tmp);
                if (tmp.len < combine.len || ((tmp.len == combine.len) && (tmp.rep > combine.rep))) {
                    combine = tmp;
                }
            }
            seq[start][end] = combine;
        }
    }

    Sequence result;
    build(seq[0][len - 1], &result);
    printf("%s\n", result.str);
}


void setSequence(Sequence *seq, const char *str, int len, int rep) {
    strcpy(seq->str, str);
    seq->len = len;
    seq->rep = rep;
}

void combineSequence(Sequence a, Sequence b, Sequence *combined) {
    if (strcmp(a.str, b.str) == 0) {
        setSequence(combined, a.str, a.len, a.rep + b.rep);
    }
    else {
        Sequence l, r;
        build(a, &l);
        build(b, &r);
        char str[MAX_LENGTH];
        strcpy(str, l.str);
        strcat(str, r.str);
        setSequence(combined, str, l.len + r.len, 1);
    }
}

void build(Sequence oriSeq, Sequence *result) {
    char strRep[MAX_LENGTH];
    sprintf(strRep, "%d", oriSeq.rep);
    int strRepLen = strlen(strRep);

    int foldLen = oriSeq.len + strRepLen + 2, notFoldLen = oriSeq.len * oriSeq.rep;
    bool needFold = foldLen < notFoldLen;

    char strBuild[MAX_LENGTH] = { '\0' };
    if (needFold) {
        sprintf(strBuild, "%d(%s)", oriSeq.rep, oriSeq.str);
        setSequence(result, strBuild, foldLen, 1);
    } else {
        for (int i = 1; i <= oriSeq.rep; ++i) {
            strcat(strBuild, oriSeq.str);
        }
        setSequence(result, strBuild, notFoldLen, 1);
    }
}