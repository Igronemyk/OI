#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        int c;
        cin >> c;
        int *dp = new int[c + 1],*sum = new int[c + 1];
        dp[0] = 0;
        sum[0] = 0;
        for(int i = 1;i <= c;i++){
            int num,value;
            cin >> num >> value;
            sum[i] = sum[i - 1] + num;
            int minResult = -1;
            for(int j = 1;j <= i;j++){
                if(minResult == -1 || minResult > (dp[j - 1] + (sum[i] - sum[j - 1] + 10)*value)){
                    minResult = dp[j - 1] + (sum[i] - sum[j - 1] + 10)*value;
                }
            }
            dp[i] = minResult;
        }
        cout << dp[c] << endl;
    }
    return 0;
}
