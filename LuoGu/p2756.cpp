#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

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

};

bool agument(int now,bool *visit,int *match,Graph &graph) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        visit[tmpEdge.to] = true;
        if(match[tmpEdge.to] == -1 || agument(match[tmpEdge.to],visit,match,graph)) {
            match[tmpEdge.to] = now;
            match[now] = tmpEdge.to;
            return true;
        }
    }
    return false;
}

int maxMatch(Graph &graph,int size,int trySize,bool *visit,int *match) {
    int result = 0;
    memset(match,-1,sizeof(int) * size);
    for(int i = 0;i < trySize;i++) {
        memset(visit,false,sizeof(bool) * size);
        if(agument(i,visit,match,graph)) {
            result++;
        }
    }
    return result;
}

int main() {
    int m = read<int>(),n = read<int>();
    Graph graph(n * n,n);
    int u = read<int>(),v = read<int>();
    while(u != -1 && v != -1) {
        u--; v--;
        graph.addEdge(u,v);
        u = read<int>(),v = read<int>();
    }
    bool *visit = new bool[n];
    int *match = new int[n];
    printf("%d\n",maxMatch(graph,n,m,visit,match));
    for(int i = 0;i < m;i++) {
        if(match[i] == -1) continue;
        printf("%d %d\n",i + 1,match[i] + 1);
    }
    delete[] visit;
    delete[] match;
    return 0;
}
