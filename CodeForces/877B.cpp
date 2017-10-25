#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int dp[5000][5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int length = static_cast<int>(s.size());
    memset(dp,INF,sizeof(dp));
    int result = 1;
    if(s[0] == 'a') {
        dp[0][0] = 0;
        dp[0][1] = 1;
    }else {
        dp[0][0] = 1;
        dp[0][1] = 0;
    }
    for(int i = 1;i < length;i++) {
        char tmpChar = s[i];
        dp[i][0] = min(dp[i][0],dp[i - 1][0] + (tmpChar == 'a' ? 0 : 1));
        dp[i][1] = min(dp[i][1],dp[i - 1][1] + (tmpChar == 'b' ? 0 : 1));
        dp[i][2] = min(dp[i][2],dp[i - 1][2] + (tmpChar == 'b' ? 0 : 1));
        dp[i][3] = min(dp[i][3],dp[i - 1][3] + (tmpChar == 'a' ? 0 : 1));
        dp[i][4] = min(dp[i][4],dp[i - 1][4] + (tmpChar == 'a' ? 0 : 1));
        if(tmpChar == 'b') {
            dp[i][2] = min(dp[i][2],dp[i - 1][0]);
        }
        if(tmpChar == 'a') {
            dp[i][3] = min(dp[i][3],dp[i - 1][1]);
            dp[i][4] = min(dp[i][4],dp[i - 1][2]);
        }
        for(int j = 0;j < 5;j++) {
            if(dp[i][j] != INF) {
                result = max(result,i + 1 - dp[i][j]);
            }
        }
    }
    cout << result << endl;
    return 0;
}

