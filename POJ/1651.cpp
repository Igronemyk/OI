#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;


int main(){
    int N;
    scanf("%d",&N);
        int *values = new int[N + 1];
        int **dp = new int*[N + 1];
        for(int i = 0;i <= N;i++){
            dp[i] = new int[N + 1];
            fill(dp[i],dp[i] + N + 1,(i == 1 || i == 2) ? 0 : INF);
        }
        for(int i = 0;i < N;i++){
            scanf("%d",&values[i]);
        }
        for(int len = 3;len <= N;len++){
            for(int i = 0;i <= N - len;i++){
                for(int j = i + 1;j < i + len - 1;j++){
                    dp[len][i] = min(dp[len][i],dp[j - i + 1][i] + dp[(i + len - 1) - j + 1][j] + values[i] * values[j] * values[i + len - 1]);
                }
            }
        }
        printf("%d\n",dp[N][0]);
    return 0;
}
