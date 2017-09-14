#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

inline int read(){
    int result = 0,f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n,m;
    while(true){
        n = read(),m = read();
        if(n == 0 && m == 0){
            break;
        }
        int **sumA = new int*[n],**sumB = new int*[m];
        for(int i = 0;i <= m;i++){
            sumB[i] = new int[n + 1];
            sumB[i][0] = 0;
        }
        for(int i = 0;i < n;i++){
            sumA[i] = new int[m + 1];
            sumA[i][0] = 0;
            for(int j = 1;j <= m;j++){
                int tmpValue = read();
                sumA[i][j] = sumA[i][j - 1] + tmpValue;
            }
        }
        for(int i = 1;i <= n;i++){
            for(int j = 0;j < m;j++){
                int tmpValue = read();
                sumB[j][i] = sumB[j][i - 1] + tmpValue;
            }
        }
        int **dp = new int*[n + 1];
        for(int i = 0;i <= n;i++){
            dp[i] = new int[m + 1];
            fill(dp[i],dp[i] + m + 1,0);
        }
        for(int i = 1; i <= n;i++){
            for(int j = 1;j <= m;j++){
                dp[i][j] = max(dp[i][j - 1] + sumB[j - 1][i],dp[i - 1][j] + sumA[i - 1][j]);
            }
        }
        cout << dp[n][m] << endl;
    }
    return 0;
}
//dp[i][j]为前i行前j列矿物最大值
//dp[i][j - 1] || dp[i - 1][j]
