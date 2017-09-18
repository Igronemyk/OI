#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read(),m = read(),k = read();
    long long *value = new long long[n + 1];
    value[0] = 0;
    for(int i = 1;i <= n;i++){
        int tmpValue = read();
        value[i] = value[i - 1] + tmpValue;
    }
    long long **dp = new long long*[n + 1];
    for(int i = 0;i <= n;i++) {
        dp[i] = new long long[k + 1];
        fill(dp[i],dp[i] + k + 1,0);
    }
    for(int i = m;i <= n;i++){
        for(int j = 1;j <= k;j++){
            dp[i][j] = max(dp[i][j],dp[i - 1][j]);
            dp[i][j] = max(dp[i][j],dp[i - m][j - 1] + value[i] - value[i - m]);
        }
    }
    printf("%lld\n",dp[n][k]);
    return 0;
}
