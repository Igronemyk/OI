#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f;

inline int read(){
    int result = 0, f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f*= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c -'0';c = getchar();}
    return result * f;
}

int main(){
    while(true){
        int n = read();
        if(n == 0) break;
        int **dis = new int*[n + 1];
        for(int i = 0;i < n + 1;i++){
            dis[i] = new int[n + 1];
        }
        for(int i = 0;i < n +1;i++){
            for(int j = 0;j < n + 1;j++){
                dis[i][j] = read();
            }
        }
        for(int k = 0;k <= n;k++){
            for(int i = 0;i <= n;i++){
                for(int j = 0;j <= n;j++){
                    if(dis[i][k] + dis[k][j] < dis[i][j]) dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
        int maxState = (1 << (n + 1)) - 1;
        int **dp = new int*[n + 1];
        for(int i = 0;i < n + 1;i++){
            dp[i] = new int[maxState +1];
            fill(dp[i],dp[i] + maxState + 1,INF);
        }
        dp[0][0] = 0;
        for(int i = 0;i <= maxState;i++){
            for(int j = 0;j <= n;j++){
                if(dp[j][i] == INF) continue;
                for(int k = 0;k <= n;k++){
                    if(i & (1 << k)) continue;
                    dp[k][i | (1 << k)] = min(dp[k][i | (1 << k)],dp[j][i] + dis[j][k]);
                }
            }
        }
        printf("%d\n",dp[0][maxState]);
    }
    return 0;
}
