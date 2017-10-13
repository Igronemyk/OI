#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

void compress(int *stones,int M,int T){
    for(int i = 0;i < M - 1;i++){
        int nowValue = stones[i],nextValue = stones[i + 1];
        int cutLength = (nextValue - nowValue - T * 2) / T * T;
        if(cutLength <= 1) continue;
        for(int j = i + 1;j < M;j++){
            stones[j] -= cutLength;
        }
    }
}

int main() {
    int L = read<int>(),S = read<int>(),T = read<int>(),M = read<int>();
    int *stones = new int[M];
    for(int i = 0;i < M;i++) stones[i] = read<int>();
    sort(stones,stones + M);
    compress(stones,M,T);
    int maxLength = stones[M - 1] + 1;
    int *dp = new int[maxLength + 1];
    memset(dp,INF,sizeof(int) * (maxLength + 1));
    dp[0] = 0;
    for(int i = 0;i < M;i++) dp[stones[i]]++;
    for(int i = 1;i <= maxLength;i++){
        bool isStone = (dp[i] == INF + 1) ? true : false;
        for(int j = S;j <= T && i - j >= 0;j++){
            dp[i] = min(dp[i],dp[i - j]);
        }
        if(isStone) dp[i]++;
    }
    int result = INF;
    for(int i = maxLength - S;i <= maxLength;i++){
        result = min(result,dp[i]);
    }
    printf("%d\n",result);
    return 0;
}
