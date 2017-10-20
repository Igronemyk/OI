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

const int MAXN = 6000;

namespace Adj {
    struct Node {
        int to,next;
    } nodes[MAXN * 2];
    int tot,heads[MAXN];

    void init() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }

}

using namespace Adj;

void dfs(int now,int father,int *values,int **dp) {
    if(nodes[heads[now]].next == -1 && nodes[heads[now]].to == father) {
        dp[now][0] = 0;
        dp[now][1] = max(0,values[now]);
    }
    int countSum1 = 0,countSum2 = 0;
    for(int i = heads[now];i != -1;i = nodes[i].next) {
        if(nodes[i].to == father) continue;
        dfs(nodes[i].to,now,values,dp);
        countSum1 += dp[nodes[i].to][0];
        countSum2 += dp[nodes[i].to][1];
    }
    dp[now][0] = countSum2;
    dp[now][1] = max(0,values[now]) + countSum1;
}

int main() {
    init();
    int N = read<int>();
    int *values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    int **dp = new int*[N];
    for(int i = 0;i < N;i++) {
        dp[i] = new int[2];
        memset(dp[i],0,sizeof(dp[i]) * 2);
    }
    for(int i = 0;i < N - 1;i++) {
        int from = read<int>(),to = read<int>();
        from--;to--;
        addEdge(from,to);
        addEdge(to,from);
    }
    dfs(0,-1,values,dp);
    printf("%d\n",max(dp[0][0],dp[0][1]));
    return 0;
}
