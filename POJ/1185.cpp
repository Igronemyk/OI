#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int N,M;
    while(cin >> N >> M){
        int maxState = 1 << M;
        int *rowState = new int[N],*state = new int[maxState],stateCount = 0,*num = new int[maxState];
        for(int i = 0;i < maxState;i++) {
            if((i & (i << 1)) == 0 && (i & (i << 2)) == 0){
                state[stateCount] = i;
                int tmpValue = i,tmpCount = 0;
                while(tmpValue){
                    tmpValue = tmpValue & (tmpValue - 1);
                    tmpCount++;
                }
                num[stateCount] = tmpCount;
                stateCount++;
            }
        }
        fill(rowState,rowState + N,0);
        for(int i = 0;i < N;i++){
            string s;
            cin >> s;
            for(string::iterator it = s.begin();it != s.end();it++){
                rowState[i] = (rowState[i] << 1) | (*it == 'H' ? 0 : 1);
            }
        }
        int ***dp = new int**[N];
        for(int i = 0;i < N;i++){
            dp[i] = new int*[stateCount];
            for(int j = 0;j < stateCount;j++){
                dp[i][j] = new int[stateCount];
                fill(dp[i][j],dp[i][j] + stateCount,0);
            }
        }
        for(int i = 0;i < stateCount;i++){
            if((state[i] & rowState[0]) != state[i]) continue;
            fill(dp[0][i],dp[0][i] + stateCount,num[i]);
        }
        if(N > 1) {
            for(int i = 0;i < stateCount;i++){
                if((state[i] & rowState[1]) != state[i]) continue;
                for(int j = 0;j < stateCount;j++){
                    if(state[i] & state[j]) continue;
                    dp[1][i][j] = dp[0][j][0] + num[i];
                }
            }
        }
        for(int i = 2;i < N;i++){
            for(int j = 0;j < stateCount;j++){
                if((state[j] & rowState[i]) != state[j]) continue;
                for(int k = 0;k < stateCount;k++){
                    if(state[j] &state[k]) continue;
                    for(int l = 0;l < stateCount;l++){
                        if((state[j] & state[l]) || (state[k] & state[l])) continue;
                        dp[i][j][k] = max(dp[i][j][k],dp[i - 1][k][l]);
                    }
                    dp[i][j][k] += num[j];
                }
            }
        }
        int result = 0;
        for(int i = 0;i < stateCount;i++){
            for(int j = 0;j < stateCount;j++){
                result = max(result,dp[N - 1][i][j]);
            }
        }
        cout << result << endl;
    }
    return 0;
}
