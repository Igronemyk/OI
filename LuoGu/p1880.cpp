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
    int *value = new int[N],*index = new int[2 * N + 1];
    index[0] = 0;
    for(int i = 0;i < N;i++) {
        value[i] = read<int>();
        index[i + 1] = index[i] + value[i];
    }
    for(int i = N;i < 2 * N;i++) {
        index[i + 1] = index[i] + value[i - N];
    }
    int **dp = new int*[N + 1];
    int **dpMax = new int*[N + 1];
    for(int i = 0;i <= N;i++) {
        dp[i] = new int[2 * N];
        memset(dp[i],INF,sizeof(int) * 2 * N);
        dpMax[i] = new int[2 * N];
        memset(dpMax[i],0,sizeof(int) * 2 * N);
    }
    memset(dp[1],0,sizeof(int) * 2 * N);
    for(int len = 2;len <= N;len++) {
        for(int left = 0;left <= 2 * N - len;left++) {
            int right = left + len - 1;
            for(int cutPoint = left;cutPoint < right;cutPoint++) {
                dp[len][left] = min(dp[len][left],dp[cutPoint - left + 1][left] + dp[right - cutPoint][cutPoint + 1] + index[right + 1] - index[left]);
                dpMax[len][left] = max(dpMax[len][left],dpMax[cutPoint - left + 1][left] + dpMax[right - cutPoint][cutPoint + 1] + index[right + 1] - index[left]);
            }
        }
    }
    int minValue = INF,maxValue = 0;
    for(int i = 0;i < N;i++) {
        minValue = min(minValue,dp[N][i]);
        maxValue = max(maxValue,dpMax[N][i]);
    }
    printf("%d\n%d\n",minValue,maxValue);
    return 0;
}
