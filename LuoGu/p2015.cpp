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

int N,Q;

void dfs(int now,int father,Graph &graph,int **dp) {
    int leftChild = -1,rightChild = -1,childsEdgeWeight = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        if(leftChild == -1) {
            leftChild = tmpEdge.to;
        }else {
            rightChild = tmpEdge.to;
        }
        childsEdgeWeight += tmpEdge.weight;
        dfs(tmpEdge.to,now,graph,dp);
        for(int j = 1;j <= Q;j++) {
            dp[now][j] = max(dp[now][j],dp[tmpEdge.to][j - 1] + tmpEdge.weight);
        }
    }
    if(leftChild == -1 && rightChild == -1) {
        return;
    }
    for(int i = 2;i <= Q;i++) {
        for(int j = 0;j <= i - 2;j++) {
            dp[now][i] = max(dp[now][i],dp[leftChild][j] + dp[rightChild][i - j - 2] + childsEdgeWeight);
        }
    }
}


int main() {
    N = read<int>();
    Q = read<int>();
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    int **dp = new int*[N];
    for(int i = 0;i < N;i++) {
        dp[i] = new int[Q + 1];
        memset(dp[i],0,sizeof(int) * (Q + 1));
    }
    dfs(0,-1,graph,dp);
    printf("%d\n",dp[0][Q]);
    return 0;
}
