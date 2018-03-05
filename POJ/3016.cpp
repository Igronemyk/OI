#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 1010;
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXK = 11;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

void getCost(int n) {

}



int main() {
    srand(123456);
    int n,k;
    while(~scanf("%d%d",&n,&k)) {
        if(n == 0 && k == 0) break;
        memset(costs,INF,sizeof(costs));
        memset(dp,INF,sizeof(dp));
        for(int i = 1;i <= n;i++) {
            values[i] = read<int>();
        }
        memcpy(tmpValue + 1,values + 1,sizeof(int) * n);
        for(int i = 1;i <= n;i++) {
            tmpValue[i] -= i;
        }
        getCost(n);
        memcpy(tmpValue + 1,values + 1,sizeof(int) * n);
        for(int i = 1;i <= n;i++) {
            tmpValue[i] = -tmpValue[i] - i;
        }
        getCost(n);
        dp[0][0] = 0;
        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= k;j++) {
                for(int l = j - 1;l < i;l++) {
                    dp[i][j] = min(dp[i][j],dp[l][j - 1] + costs[l + 1][i]);
                }
            }
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}
