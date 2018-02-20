#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 200010;

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
} graph(MAXN * 2,MAXN);

bool visit[MAXN];
int subMax[2][MAXN],allMax[2][MAXN];
int n;

void dfs(int now,int father) {
    int nowFirstMaxDepth = 0,nowSecondMaxDepth = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to]) continue;

    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0;i < n - 1;i++) {

    }
    return 0;
}
