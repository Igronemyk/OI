#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = 100;
const int INF = 0x3f3f3f3f;

int weight[MAXN + 1][MAXN + 1];

int main() {
    int n,m;
    while(~scanf("%d%d",&n,&m)) {
        memset(weight,INF,sizeof(weight));
        for(int i = 1;i <= n;i++) {
            weight[i][i] = 0;
        }
        while(m--) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            weight[u][v] = min(weight[u][v],w);
            weight[v][u] = min(weight[v][u],w);
        }
        for(int k = 1;k <= n;k++) {
            for(int i = 1;i <= n;i++) {
                for(int j = 1;j <= n;j++) {
                    if(weight[i][j] > weight[i][k] + weight[k][j]) {
                        weight[i][j] = weight[i][k] + weight[k][j];
                    }
                }
            }
        }
        printf("%d\n",weight[1][n]);
    }
    return 0;
}
