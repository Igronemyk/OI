#include <iostream>
#include <algorithm>

using namespace std;

bool isMatch(char a,char b){
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

int main(){
    ios::sync_with_stdio(false);
    string s;
    while(cin >> s){
        if(s == "end") break;
        int length = static_cast<int>(s.size());
        int **dp = new int*[length];
        for(int i = 0;i < length;i++){
            dp[i] = new int[length];
            fill(dp[i],dp[i] + length,0);
        }
        for(int len = 2;len <= length;len++){
            for(int i = 0;i <= length - len;i++){
                int j = i + len - 1;
                for(int k = i;k < j;k++){
                    dp[i][j] = max(dp[i][j],dp[i][k] + dp[k + 1][j]);
                }
                if(isMatch(s[i],s[j])) dp[i][j] = max(dp[i][j],dp[i + 1][j - 1] + 1);
            }
        }
        cout << dp[0][length - 1] * 2 << endl;
    }
    return 0;
}
