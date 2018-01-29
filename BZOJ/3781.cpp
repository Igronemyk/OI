#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Query {
    int l,r,block,sign;

    bool operator < (const Query &otherQuery) const {
        if(block != otherQuery.block) {
            return block < otherQuery.block;
        }
        return r < otherQuery.r;
    }
};

int powSelf(int value) {
    return value * value;
}

int main() {
    int N = read<int>(),M = read<int>(),K = read<int>(),*values = new int[N],*cnts = new int[K + 1];
    memset(cnts,0,sizeof(int) * (K + 1));
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    int sqrtValue = sqrt(N),*results = new int[M];
    Query *querys = new Query[M];
    for(int i = 0;i < M;i++) {
        querys[i].l = read<int>() - 1;
        querys[i].r = read<int>() - 1;
        querys[i].block = querys[i].l / sqrtValue;
        querys[i].sign = i;
    }
    sort(querys,querys + M);
    int nowLeft = -1,nowRight = -1;
    long long result = 0;
    for(int i = 0;i < M;i++) {
        Query &tmpQuery = querys[i];
        if(nowLeft == - 1 && nowRight == -1) {
            for(int j = tmpQuery.l;j <= tmpQuery.r;j++) {
                result -= powSelf(cnts[values[j]]);
                cnts[values[j]]++;
                result += powSelf(cnts[values[j]]);
            }
            nowLeft = tmpQuery.l;
            nowRight = tmpQuery.r;
        }else {
            while(tmpQuery.l > nowLeft) {
                result -= powSelf(cnts[values[nowLeft]]);
                cnts[values[nowLeft]]--;
                result += powSelf(cnts[values[nowLeft]]);
                nowLeft++;
            }
            while(tmpQuery.l < nowLeft) {
                nowLeft--;
                result -= powSelf(cnts[values[nowLeft]]);
                cnts[values[nowLeft]]++;
                result += powSelf(cnts[values[nowLeft]]);
            }
            while(nowRight < tmpQuery.r) {
                nowRight++;
                result -= powSelf(cnts[values[nowRight]]);
                cnts[values[nowRight]]++;
                result += powSelf(cnts[values[nowRight]]);
            }
            while(nowRight > tmpQuery.r) {
                result -= powSelf(cnts[values[nowRight]]);
                cnts[values[nowRight]]--;
                result += powSelf(cnts[values[nowRight]]);
                nowRight--;
            }
        }
        results[tmpQuery.sign] = result;
    }
    for(int i = 0;i < M;i++) {
        printf("%d\n",results[i]);
    }
    return 0;
}
