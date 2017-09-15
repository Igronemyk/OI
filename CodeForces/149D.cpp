#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

const int MODDER = static_cast<int>(1e9 + 7);


bool check(int color1,int color2){
    return color1 == 0 || color2 == 0 || color1 != color2;
}

long long solve(int left,int right,int color1,int color2,long long ****dp,int *match){
    if(dp[left][right][color1][color2] != -1) return dp[left][right][color1][color2];
    if(left >= right){
        dp[left][right][color1][color2] = 0;
        return dp[left][right][color1][color2];
    }
    int matchIndex = match[left];
    long long result = 0;
    if(matchIndex == right){
        if((color1 == 0 && color2 != 0) || (color1 != 0 && color2 == 0)){
            if(left + 1 == right){
                dp[left][right][color1][color2] = 1;
                return dp[left][right][color1][color2];
            }
            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    if(check(color1,i) && check(j,color2)) result = (result + solve(left + 1,right - 1,i,j,dp,match))%MODDER;
                }
            }
        }
    }else{
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(check(i,j)) result = (result + solve(left,matchIndex,color1,i,dp,match) * solve(matchIndex + 1,right,j,color2,dp,match))%MODDER;
            }
        }
    }
    dp[left][right][color1][color2] = result;
    return dp[left][right][color1][color2];
}

int main(){
    string s;
    cin >> s;
    int length = static_cast<int>(s.size());
    int *match = new int[length];
    fill(match,match + length,0);
    stack<int> stk;
    for(int i = 0;i < length;i++){
        if(s[i] == '('){
            stk.push(i);
        }else{
            match[stk.top()] = i;
            stk.pop();
        }
    }
    long long ****dp = new long long***[length];
    for(int i = 0;i < length;i++){
        dp[i] = new long long**[length];
        for(int j = 0;j < length;j++){
            dp[i][j] = new long long*[3];
            for(int k = 0;k < 3;k++){
                dp[i][j][k] = new long long[3];
                fill(dp[i][j][k],dp[i][j][k] + 3,-1);
            }
        }
    }
    long long result = 0;
    for(int i = 0;i < 3;i++){
       for(int j = 0;j < 3;j++){
            result = (result + solve(0,length - 1,i,j,dp,match))%MODDER;
       }
    }
    cout << result << endl;
    return 0;
}
