#include <cstdio>
#include <algorithm>

using namespace std;

const int MODDER = 100000000;

int main(){
    int M,N;
    while(~scanf("%d%d",&M,&N)){
        int maxState = 1 << N,stateCount = 0;
        int *state = new int[maxState + 1],*rowState = new int[M];
        for(int i = 0;i < maxState;i++){
            if(!(i & (i << 1))){
                state[stateCount++] = i;
            }
        }
        fill(rowState,rowState + M,0);
        for(int i = 0;i < M;i++){
            for(int j = 0;j <N;j++){
                int tmpState;
                scanf("%d",&tmpState);
                rowState[i] = (rowState[i] << 1) | tmpState;
            }
        }
        int **dp = new int*[M];
        for(int i = 0;i < M;i++){
            dp[i] = new int[stateCount];
            fill(dp[i],dp[i] + stateCount,0);
        }
        for(int i = 0;i < stateCount;i++) if((rowState[0] & state[i]) == state[i]) dp[0][i] = 1;
        for(int i = 1;i < M;i++){
            for(int j = 0;j < stateCount;j++){
                if((rowState[i] & state[j]) != state[j]) continue;
                for(int k = 0;k < stateCount;k++){
                    if(dp[i - 1][k] && (state[j] & state[k]) == 0) dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MODDER;
                }
            }
        }
        int result = 0;
        for(int i = 0;i <stateCount;i++) if(dp[M -1][i]) result = (result +dp[M - 1][i])%MODDER;
        printf("%d\n",result);
    }
    return 0;
}
