#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0'){if(c == '-') f * -1;c = getchar();}
    while(c <= '9' && c >= '0'){result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read(), m = read();
    if(n > m){
        printf("YES");
        return 0;
    }
    bool **dp = new bool*[n + 1];
    for(int i = 0;i <= n;i++){
        dp[i] = new bool[m];
        fill(dp[i],dp[i] + m,false);
    }
    dp[0][0] = 1;
    bool solved = false;
    for(int i = 1;i <= n;i++){
        int tmpValue = read();
        for(int j = 0;j < m;j++){
            int x = ((j - tmpValue)% m + m)%m;
            if(dp[i - 1][x]){
                dp[i][j] = true;
                if(j == 0){
                    solved = true;
                    goto outside;
                }
            }
            if(dp[i - 1][j]) dp[i][j] = true;
        }
    }
    outside:
    printf(solved ? "YES" : "NO");
    return 0;
}
