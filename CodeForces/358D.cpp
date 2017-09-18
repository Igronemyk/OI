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
    int n = read();
    int **value = new int*[n];
    for(int i = 0;i < n;i++) value[i] = new int[3];
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < n;j++){
            value[j][i] = read();
        }
    }
    int **dp = new int*[n];
    for(int i = 0;i < n;i++) dp[i] = new int[2];
    dp[0][0] = value[0][0];dp[0][1] = value[0][1];
    for(int i = 1;i < n;i++){
        for(int j = 0;j < 2;j++){
            dp[i][j] = 0;
            for(int k = 0;k < 2;k++){
                dp[i][j] = max(dp[i][j],dp[i - 1][k] + value[i][1 - k + j]);
            }
        }
    }
    printf("%d\n",dp[n - 1][0]);
    return 0;
}
