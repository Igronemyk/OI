#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main(){
    int N;
    while(~scanf("%d",&N)){
        int *nums = new int[N];
        for(int i = 0;i < N;i++){
            scanf("%d",&nums[i]);
        }
        int **dp = new int*[N];
        for(int i = 0;i < N;i++){
            dp[i] = new int[N];
            fill(dp[i],dp[i] + N,0);
        }
        for(int i = 0;i < N;i++){
            dp[i][i] = 1;
        }
        for(int len =2;len <= N;len++){
            for(int i = 0;i <= N - len;i++){
                int j = i + len - 1;
                dp[i][j] = INF;
                if(nums[i] == nums[j]) dp[i][j] = min(dp[i][j],dp[i + 1][j - 1] + (i + 1 > j - 1 ? 1 : 0));
                for(int k = i;k < j;k++){
                    dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        printf("%d\n",dp[0][N - 1]);
    }
    return 0;
}
