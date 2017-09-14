#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>


using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int N,M;
    while(cin >> N >> M){
        string s;
        int *cost = new int[26];
        cin >> s;
        for(int i = 0;i < N;i++){
            string tmpStr;
            int addCost,delCost;
            cin >> tmpStr >> addCost >> delCost;
            cost[tmpStr[0] - 'a'] = min(addCost,delCost);
        }
        int **dp = new int*[M];
        for(int i = 0;i < M;i++){
            dp[i] = new int[M];
            fill(dp[i],dp[i] + M,0);
        }
        for(int i = M - 1;i >= 0;i--){
            for(int j = i + 1;j < M;j++){
                dp[i][j] = min(dp[i + 1][j] + cost[s[i] - 'a'],dp[i][j - 1] + cost[s[j] - 'a']);
                if(s[i] == s[j]){
                    dp[i][j] = min(dp[i][j],dp[i + 1][j - 1]);
                }
            }
        }
        cout << dp[0][M - 1] << endl;
    }
    return 0;
}
