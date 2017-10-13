#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data {
    int downLimit,upLimit,downLength,upLength;
    Data() : downLimit(-1) , upLimit(-1) , downLength(-1) , upLength(-1) {}
};

int main() {
    int n = read<int>(),m = read<int>(),k = read<int>();
    Data *datas = new Data[n + 1];
    for(int i = 1;i <= n;i++) {
        int X = read<int>(),Y = read<int>();
        datas[i].upLength = X;
        datas[i].downLength = Y;
        datas[i].upLimit = m + 1;
        datas[i].downLimit = 0;
    }
    for(int i = 0;i < k;i++) {
        int P = read<int>(),L = read<int>(),H = read<int>();
        datas[P].downLimit = L;
        datas[P].upLimit = H;
    }
    int **dp = new int*[n + 1];
    for(int i = 0;i < n + 1;i++) {
        dp[i] = new int[m + 1];
        memset(dp[i],INF,sizeof(int) * (m + 1));
    }
    memset(dp[0],0,sizeof(int) * (m + 1));
    int result = 0;
    for(int i = 1;i <= n;i++) {
        Data &tmpData = datas[i];
        for(int j = tmpData.downLimit + 1;j < tmpData.upLimit;j++) {
            if(j < tmpData.upLength) continue;
            dp[i][j] = min(dp[i][j],min(dp[i - 1][j - tmpData.upLength] + 1,dp[i][j - tmpData.upLength] + 1));
        }
        for(int j = tmpData.downLimit + 1;j < tmpData.upLimit;j++) {
            if(j + tmpData.downLength > m) continue;
            dp[i][j] = min(dp[i][j],dp[i - 1][j + tmpData.downLength]);
        }
        if(tmpData.upLimit == m + 1){
            for(int j = max(1,m - tmpData.upLimit);j <= m;j++){
                dp[i][m] = min(dp[i][m],min(dp[i - 1][j] + 1,dp[i][j] + 1));
            }
        }
        bool isAccepted = false;
        for(int j = 0;j <= m;j++){
            if(dp[i][j] != INF) {
                isAccepted = true;
                break;
            }
        }
        if(!isAccepted) {
            printf("0\n%d\n",result);
            return 0;
        }
        if(tmpData.upLimit != m + 1 || tmpData.downLimit != 0) result++;
    }
    result = INF;
    for(int i = 0;i <= m;i++) {
        result = min(result,dp[n][i]);
    }
    printf("1\n%d\n",result);
    return 0;
}

