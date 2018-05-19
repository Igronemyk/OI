#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 400010;
const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

int dfn[MAXN],fathers[MAXN],f[MAXN],g[MAXN],values[MAXN],nowTime;

void dp(int root,int now) {
    int prevS = 0,prevNS = 0,nowS = 0,nowNS = 0;
    for(int i = now;i != root;i = fathers[i]) {
        nowS = prevNS + f[i];
        nowNS = prevS + g[i];
        prevNS = nowNS;
        prevS = max(nowS,nowNS);
    }
    g[root] += prevS;
    prevS = 0;
    prevNS = -INF;
    for(int i = now;i != root;i = fathers[i]) {
        nowS = prevNS + f[i];
        nowNS = prevS + g[i];
        prevNS = nowNS;
        prevS = max(nowS,nowNS);
    }
    f[root] += prevNS;
}

void getResult(int now) {
    dfn[now] = ++nowTime;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dfn[tmpEdge.to] != 0) continue;
        fathers[tmpEdge.to] = now;
        getResult(tmpEdge.to);
    }
    f[now] = values[now];
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == fathers[now] || fathers[tmpEdge.to] == now || dfn[tmpEdge.to] <= dfn[now]) continue;
        dp(now,tmpEdge.to);
    }
}

int main() {
    int n = read<int>(),m = read<int>();
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
    }
    getResult(1);
    printf("%d\n",max(f[1],g[1]));
    return 0;
}
