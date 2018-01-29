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

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }

    ~Graph() {
        delete[] edges;
        delete[] heads;
    }
};

int dfs(int now,int father,Graph &graph,int **dp) {
    int nowSize = 1;
    for(int i = graph.heads[now];i != - 1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        int childSize = dfs(tmpEdge.to,now,graph,dp);
        nowSize += childSize;
        for(int nowCap = nowSize;nowCap >= 0;nowCap--) {
            for(int childCap = 0;childCap <= childSize && childCap + (now == 0 ? 0 : 1) <= nowCap;childCap++) {
                dp[now][nowCap] = max(dp[now][nowCap],dp[tmpEdge.to][childCap] + dp[now][nowCap - childCap]);
            }
        }
    }
    return nowSize;
}

int main() {
    int N,M;
    while(~scanf("%d%d",&N,&M)) {
        if(N == 0 && M == 0) break;
        int *values = new int[N + 1];
        Graph graph(N * 2,N + 1);
        for(int i = 1;i <= N;i++) {
            int prev = read<int>(),weight = read<int>();
            values[i] = weight;
            graph.addEdge(prev,i);
        }
        int **dp = new int*[N + 1];
        for(int i = 0;i <= N;i++) {
            dp[i] = new int[N + 1];
            memset(dp[i],0,sizeof(int) * (N + 1));
            if(i != 0) {
                dp[i][1] = values[i];
            }
        }
        dfs(0,-1,graph,dp);
        printf("%d\n",dp[0][M]);
        delete[] values;
        for(int i = 0;i <= N;i++) {
            delete[] dp[i];
        }
        delete dp;
    }
    return 0;
}
