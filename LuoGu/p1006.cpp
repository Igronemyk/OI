#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int value[101][101],dp[101][101][101];

int main() {
    int m = read<int>(),n = read<int>();
    for(int i = 1;i <= m;i++) {
        for(int j = 1;j <= n;j++) {
            value[i][j] = read<int>();
        }
    }
    for(int len = 1;len <= m + n - 1;len++) {
        for(int i = 1;i <= m;i++) {
            for(int j = 1;j <= m;j++) {
                int k = len - i + 1,l = len - j + 1;
                if(k < 1 || l < 1) continue;
                dp[len][i][j] = max(max(dp[len - 1][i][j],dp[len - 1][i - 1][j - 1]),max(dp[len - 1][i - 1][j],dp[len - 1][i][j - 1])) + value[i][k] + value[j][l];
                if(i == j) dp[len][i][j] -= value[i][k];
            }
        }
    }
    printf("%d\n",dp[m + n - 1][m][m]);
    return 0;
}
