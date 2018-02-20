#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c=  getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int dp[MAXN][MAXN],values[MAXN];

int main() {
    int n;
    while(~scanf("%d",&n)) {
        if(n == 0) break;
        memset(dp,0,sizeof(dp));
        for(int i = 1;i <= n;i++) {
            values[i] = read<int>();
            dp[i][i] = 1;
        }
        for(int nowLen = 2;nowLen <= n;nowLen++) {
            for(int startPos = 1;startPos + nowLen - 1 <= n;startPos++) {
                int endPos = startPos + nowLen - 1;
                dp[startPos][endPos] = max(dp[startPos + 1][endPos],dp[startPos][endPos - 1]);
                if(values[startPos] == values[endPos]) {
                    dp[startPos][endPos] = max(dp[startPos][endPos],dp[startPos + 1][endPos - 1] + 2);
                }
            }
        }
        int result = 0;
        for(int i = 1;i <= n;i++) {
            result = max(result,dp[1][i] + dp[i + 1][n]);
        }
        printf("%d\n",result);
    }
    return 0;
}
