#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long calUp(int j,int k,long long *sumValues,long long *dp) {
    return (dp[j] + sumValues[j] * sumValues[j]) - (dp[k] + sumValues[k] * sumValues[k]);
}

long long calDown(int j,int k,long long *sumValues,long long *dp) {
    return 2 * (sumValues[j] - sumValues[k]);
}

int main() {
    int N,M;
    while(~scanf("%d%d",&N,&M)) {
        int *values = new int[N + 1],*que = new int[N + 1],nowPos = 0,head = 0,tail = 0;
        long long *sumValues = new long long[N + 1],*dp = new long long[N + 1];
        sumValues[0] = 0;
        dp[0] = 0;
        que[tail++] = 0;
        for(int i = 1;i <= N;i++) {
            values[i] = read<int>();
            sumValues[i] = sumValues[i - 1] + values[i];
            while(head + 1 < tail && calUp(que[head + 1],que[head],sumValues,dp) <= sumValues[i] * calDown(que[head + 1],que[head],sumValues,dp)) head++;
            dp[i] = dp[que[head]] + (sumValues[i] - sumValues[que[head]]) * (sumValues[i] - sumValues[que[head]]) + M;
            while(head + 1 < tail && calUp(que[tail - 1],que[tail - 2],sumValues,dp) * calDown(i,que[tail - 1],sumValues,dp) >= calUp(i,que[tail - 1],sumValues,dp) * calDown(que[tail - 1],que[tail - 2],sumValues,dp)) tail--;
            que[tail++] = i;
        }
        printf("%lld\n",dp[N]);
        delete[] values;
        delete[] que;
        delete[] sumValues;
        delete[] dp;
    }
    return 0;
}
