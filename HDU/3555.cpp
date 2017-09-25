#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

inline int readInt(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

inline long long readLong(){
    long long result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(f == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long myPow(int a,int b){
    long long result = 1,base = a;
    while(b){
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

long long dp[21][10],nums[21],dp_limit[21];

long long solve(long long num){
    memset(nums,0,sizeof(nums));
    memset(dp_limit,0,sizeof(dp_limit));
    long long result = 0,length = 0;
    while(num){
        nums[length++] = num%10;
        num /= 10;
    }
    for(int i = 0;i < nums[length - 1];i++){
        result += dp[length][i];
    }
    dp_limit[1] = dp[1][nums[0]];
    for(int i = 2;i <= length;i++){
        for(int j = 0;j <= nums[i - 2];j++){
            if(j == nums[i - 2]){
                dp_limit[i] += dp_limit[i - 1];
            }else{
                dp_limit[i] += dp[i - 1][j];
            }
            if(nums[i -1] == 4 && j == 9) dp_limit[i] += myPow(10,i - 2);
        }
    }
    result += dp_limit[length];
    return result;
}

int main(){
    int T = readInt();
    for(int i = 0;i < 10;i++) dp[1][i] = 0;
    for(int i = 2;i <= 20;i++){
        for(int j = 0;j < 10;j++){
            for(int k = 0;k < 10;k++){
                dp[i][j] += dp[i - 1][k];
                if(j == 4 && k == 9) dp[i][j] += myPow(10,i - 2);
            }
        }
    }
    /*
    while(T--){
        long long N = readLong();
        printf("%lld\n",solve(N));
    }*/
    for(int i = 0;i < 10;i++){
        printf("%lld ",dp[4][i]);
    }
    //i = 20
    // que: dp[5][0] = 300 or 299?
    return 0;
}
//499
//0 ~ 399  99
