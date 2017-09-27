#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int N,K;
    cin >> N >> K;
    int *values = new int[N];
    for(int i = 0;i < N;i++){
        cin >> values[i];
    }
    int maxState = 1 << N;
    long long **dp = new long long*[N];
    for(int i = 0;i < N;i++){
        dp[i] = new long long[maxState];
        fill(dp[i],dp[i] +maxState,0);
    }
    for(int i = 0;i < N;i++) dp[i][1 << i] = 1;
    /*
    for(int j = 0;j < maxState;j++){
        for(int i = 0;i < N;i++){
            if(!(j & (1 << i))) continue;
            for(int k = 0;k < N;k++){
                if((j & (1 << k)) || abs(values[k] - values[i]) <= K) continue;
                dp[k][j | (1 << k)] += dp[i][j];
            }
        }
    }*/
    for(int i = 0;i < maxState;i++){
        for(int j = 0;j < N;j++){
            if(i & (1 << j)) continue;
            for(int k = 0;k < N;k++){
                if(!(i & (1 << k)) || abs(values[k] - values[j]) <= K) continue;
                dp[j][i | (1 << j)] += dp[k][i];
            }
        }
    }
    /*
    for(int i = 0;i < N;i++){
        for(int j = 0;j < maxState;j++){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    */
    long long ans = 0;
    for(int i = 0;i < N;i++) ans += dp[i][maxState - 1];
    cout << ans;
    return 0;
}
