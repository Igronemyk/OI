#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int V = read<int>(),P = read<int>();
    int *values = new int[V + 1],*sumValues = new int[V + 1],**costs = new int*[V + 1];
    sumValues[0] = 0;
    for(int i = 1;i <= V;i++) {
        values[i] = read<int>();
        sumValues[i] = sumValues[i - 1] + values[i];
        costs[i] = new int[V + 1];
        memset(costs[i],0,sizeof(int) * (V + 1));
    }
    for(int i = 1;i <= V;i++) {
        for(int j = i;j <= V;j++) {
            if(i == j) {
                costs[i][j] = 0;
                continue;
            }
            int mid = (i + j) / 2,leftRange = mid - i + 1,rightRange = j - mid + 1;
            costs[i][j] += leftRange * values[mid] - (sumValues[mid] - sumValues[i - 1]);
            costs[i][j] += (sumValues[j] - sumValues[mid - 1]) - rightRange * values[mid];
        }
    }
    int **dp = new int*[P + 1];
    for(int i = 0;i <= P;i++) {
        dp[i] = new int[V + 1];
        memset(dp[i],INF,sizeof(int) * (V + 1));
    }
    dp[0][0] = 0;
    for(int i = 1;i <= P;i++) {
        for(int j = i;j <= V;j++) {
            for(int k = 0;k < j;k++) {
                dp[i][j] = min(dp[i][j],dp[i - 1][k] + costs[k + 1][j]);
            }
        }
    }
    printf("%d\n",dp[P][V]);
    return 0;
}
