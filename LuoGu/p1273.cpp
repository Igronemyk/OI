#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int weight) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = weight;
        heads[u] = tot++;
    }

};

int N,M;

int dfs(int now,Graph &graph,int **dp) {
    if(now >= N - M) {
        return 1;
    }
    int nowSize = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        int childSize = dfs(tmpEdge.to,graph,dp);
        nowSize += childSize;
        for(int nowCap = nowSize;nowCap >= 0;nowCap--) {
            for(int childCap = 0;childCap <= childSize && childCap <= nowCap;childCap++) {
                dp[now][nowCap] = max(dp[now][nowCap],dp[tmpEdge.to][childCap] + dp[now][nowCap - childCap] - tmpEdge.weight);
            }
        }
    }
    return nowSize;
}


int main() {
    N = read<int>(); M = read<int>();
    Graph graph(N - 1,N);
    for(int i = 0;i < N - M;i++) {
        int childSize = read<int>();
        for(int child = 0;child < childSize;child++) {
            int childSign = read<int>(),weight = read<int>();
            childSign--;
            graph.addEdge(i,childSign,weight);
        }
    }
    int **dp = new int*[N];
    for(int i = 0;i < N;i++) {
        dp[i] = new int[M + 1];
        fill(dp[i],dp[i] + M + 1,-INF);
        if(i >= N - M) {
            dp[i][1] = read<int>();
        }
        dp[i][0] = 0;
    }
    dfs(0,graph,dp);
    int result = -1;
    for(int i = M;i >= 0;i--) {
        if(dp[0][i] >= 0) {
            result = i;
            break;
        }
    }
    printf("%d\n",result);
    return 0;
}
