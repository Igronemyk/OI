#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>(),M = read<int>();
    int **sumValue = new int*[M];
    for(int i = 0;i < M;i++) {
        sumValue[i] = new int[N + 1];
        memset(sumValue[i],0,sizeof(int) * (N + 1));
    }
    for(int i = 1;i <= N;i++) {
        int sign = read<int>();
        sign--;
        sumValue[sign][i]++;
    }
    for(int i = 0;i < M;i++) {
        for(int j = 1;j <= N;j++) {
            sumValue[i][j] += sumValue[i][j - 1];
        }
    }
    int maxState = (1 << M) - 1;
    int *dp = new int[maxState + 1];
    memset(dp,0,sizeof(int) * (maxState + 1));
    for(int nowState = 0;nowState <= maxState;nowState++) {
        int sortedSize = 0;
        for(int posState = 0;posState < M;posState++) {
            if(!(nowState & (1 << posState))) continue;
            sortedSize += sumValue[posState][N];
        }
        for(int posState = 0;posState < M;posState++) {
            if(!(nowState & (1 << posState))) continue;
            dp[nowState] = max(dp[nowState],dp[nowState ^ (1 << posState)] + sumValue[posState][sortedSize] - sumValue[posState][sortedSize - sumValue[posState][N]]);
        }
    }
    printf("%d\n",N - dp[maxState]);
    return 0;
}
