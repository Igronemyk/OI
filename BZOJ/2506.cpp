#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int ALPHA = 100;
const int MAXN = 1e5 + 10;
const int MAXM = 1e5 + 10;
const int MAX_VAL_RANGE = 1e4 + 10;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Operation {
    int weight,pos,p,k,sign;

    Operation() : weight(0) , pos(0) , p(0) , k(0) , sign(0) { }

    Operation(int weight,int pos,int p,int k,int sign) : weight(weight) , pos(pos) , p(p) , k(k) , sign(sign) { }

    bool operator < (const Operation &otherOperation) const {
        return pos < otherOperation.pos;
    }
} opts[MAXM * 2];

int calAll[MAX_VAL_RANGE],values[MAXN],calPre[ALPHA + 1][ALPHA + 1],result[MAXM];

int main() {
    int N = read<int>(),M = read<int>(),maxValue = 0;
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
        maxValue = max(maxValue,values[i]);
    }
    int nowIndex = 0;
    for(int i = 1;i <= M;i++) {
        int l = read<int>(),r = read<int>(),p = read<int>(),k = read<int>();
        opts[nowIndex++] = Operation(-1,l - 1,p,k,i);
        opts[nowIndex++] = Operation(1,r,p,k,i);
    }
    sort(opts,opts + nowIndex);
    int nowPos = 0;
    for(int i = 0;i <= N;i++) {
        if(i != 0) {
            for(int j = 1;j <= ALPHA;j++) {
                calPre[j][values[i] % j]++;
            }
            calAll[values[i]]++;
        }
        while(nowPos < nowIndex && opts[nowPos].pos == i) {
            Operation &tmpOpt = opts[nowPos];
            if(tmpOpt.p <= ALPHA) {
                result[tmpOpt.sign] += tmpOpt.weight * calPre[tmpOpt.p][tmpOpt.k];
            }else {
                for(int j = 0;j * tmpOpt.p + tmpOpt.k <= maxValue;j++) {
                    result[tmpOpt.sign] += tmpOpt.weight * calAll[j * tmpOpt.p + tmpOpt.k];
                }
            }
            nowPos++;
        }
    }
    for(int i = 1;i <= M;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}
