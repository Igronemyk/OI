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
        int next,to;
    } *edges;
    int tot,*heads;
    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        heads = new int[nodeSize];
        tot = 0;
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

int n,m,e;
bool *vis;
int *match;
Graph *graph;

bool dfs(int now) {
    for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
        Graph::Edge &tmpEdge = graph->edges[i];
        if(vis[tmpEdge.to]) continue;
        vis[tmpEdge.to] = true;
        if(!match[tmpEdge.to] || dfs(tmpEdge.to)) {
            match[tmpEdge.to] = now;
            return true;
        }
    }
    return false;
}

int main() {
    n = read<int>();m = read<int>();e = read<int>();
    int maxVal = max(n,m);
    vis = new bool[maxVal];
    match = new int[maxVal];
    memset(match,-1,sizeof(int) * maxVal);
    graph = new Graph(e,maxVal);
    for(int i = 0;i < e;i++) {
        int u = read<int>(),v = read<int>();
        u--;v--;
        graph->addEdge(u,v);
    }
    int result = 0;
    for(int i = 0;i < n;i++) {
        memset(vis,false,sizeof(bool) * maxVal);
        if(dfs(i)) {
            result++;
        }
    }
    printf("%d\n",result);
    return 0;
}
