#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main(){
    int N;
    while(cin >> N){
        int *value = new int[2 * N];
        bool *opt = new bool[2 * N];
        for(int i = 0;i < N;i++){
            string s;
            cin >> s;
            opt[i] = (s == "t" ? true : false);
            opt[N + i] = opt[i];
            cin >> value[i];
            value[N + i] = value[i];
        }
        int maxLen = 2 * N;
        int **dp = new int*[maxLen],**dp2 = new int*[maxLen];
        for(int i = 0;i < 2 * N;i++){
            dp[i] = new int[maxLen];
            dp2[i] = new int[maxLen];
            fill(dp[i],dp[i] + maxLen,INF * -1);
            fill(dp2[i],dp2[i] + maxLen,INF);
        }
        for(int i = 0;i < maxLen;i++){
            dp[i][i] = value[i];
            dp2[i][i] = value[i];
        }
        for(int len = 2;len <= maxLen;len++){
            for(int i = 0;i <= maxLen - len;i++){
                int j = i + len - 1;
                for(int k = i + 1;k <= j;k++){
                    if(opt[k]){
                        dp[i][j] = max(dp[i][j],dp[i][k - 1] + dp[k][j]);
                        dp2[i][j] = min(dp2[i][j],dp2[i][k - 1] + dp[k][j]);
                    }else{
                        int value1 = dp[i][k - 1] * dp[k][j];
                        int value2 = dp[i][k - 1] * dp2[k][j];
                        int value3 = dp2[i][k - 1] * dp[k][j];
                        int value4 = dp2[i][k - 1] * dp2[k][j];
                        dp[i][j] = max(dp[i][j],max(max(value1,value2),max(value3,value4)));
                        dp2[i][j] = min(dp2[i][j],min(min(value1,value2),min(value3,value4)));
                    }
                }
            }
        }
        int result = 0;
        for(int i = 0;i < N;i++){
            result = max(result,dp[i][i + N - 1]);
        }
        cout << result << endl;
        for(int i = 0;i < N;i++){
            if(result == dp[i][i + N - 1]) cout << i + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
