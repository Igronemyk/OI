#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

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
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
};

int dfs(int now,int *weight,bool *visit,Graph &graph) {
    visit[now] = true;
    int minWeight = weight[now];
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        int tmpWeight = dfs(tmpEdge.to,weight,visit,graph);
        minWeight = min(minWeight,tmpWeight);
    }
    return minWeight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    int *weights = new int[n];
    for(int i = 0;i < n;i++) cin >> weights[i];
    Graph graph(m * 2,n);
    for(int i = 0;i < m;i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    bool *visit = new bool[n];
    memset(visit,false,sizeof(bool) * n);
    long long result = 0;
    for(int i = 0;i < n;i++) {
        if(visit[i]) continue;
        result += dfs(i,weights,visit,graph);
    }
    cout << result << endl;
    return 0;
}
