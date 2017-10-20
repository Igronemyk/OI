#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>();
    int *value = new int[N],*index = new int[N + 1];
    index[0] = 0;
    for(int i = 0;i < N;i++) {
        value[i] = read<int>();
        index[i + 1] = index[i] + value[i];
    }
    int **dp = new int*[N + 1];
    for(int i = 0;i <= N;i++) {
        dp[i] = new int[N];
        memset(dp[i],INF,sizeof(int) * N);
    }
    memset(dp[1],0,sizeof(int) * N);
    for(int len = 2;len <= N;len++) {
        for(int left = 0;left <= N - len;left++) {
            int right = left + len - 1;
            for(int cutPoint = left;cutPoint < right;cutPoint++) {
                dp[len][left] = min(dp[len][left],dp[cutPoint - left + 1][left] + dp[right - cutPoint][cutPoint + 1] + index[right + 1] - index[left]);
            }
        }
    }
    printf("%d\n",dp[N][0]);
    return 0;
}
