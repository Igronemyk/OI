#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int t = read<int>();
    while(t--) {
        int M = read<int>(),N = read<int>();
        int **dp = new int*[N + 1];
        for(int i = 0;i <= N;i++) {
            dp[i] = new int[M + 1];
            memset(dp[i],0,sizeof(int) * (M + 1));
        }
        dp[0][0] = 1;
        for(int i = 1;i <= N;i++) {
            for(int j = 0;j <= M;j++) {
                if(j - i >= 0) {
                    dp[i][j] = dp[i][j - i] + dp[i - 1][j];
                }else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        printf("%d\n",dp[N][M]);
    }
    return 0;
}
