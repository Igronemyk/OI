#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

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
};

void dfs(int now,Graph &graph,int &countResult,bool *visit,bool *hasVisited) {
    visit[now] = true;
    hasVisited[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) {
            countResult++;
            continue;
        }
        if(hasVisited[tmpEdge.to]) {
            continue;
        }
        dfs(tmpEdge.to,graph,countResult,visit,hasVisited);

    }

    visit[now] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    Graph graph(n,m);
    for(int i = 0;i < m;i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        graph.addEdge(u,v);
    }
    bool *visit = new bool[n],*hasVisited = new bool[n];
    memset(visit,false,sizeof(bool) * n);
    memset(hasVisited,false,sizeof(bool) * n);
    int result = 0;
    for(int i = 0;i < n;i++) {
        if(!hasVisited[i]) {
            dfs(i,graph,result,visit,hasVisited);
            if(result > 1) {
                break;
            }
        }
    }
    if(result > 1) {
        cout << "NO" << endl;
    }else {
        cout << "YES" << endl;
    }
    return 0;
}

