#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 50010;
const int MAXN = 10010;
const int MAX_DEPTH = 14;
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
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph;

struct BCS {
    int father[MAXN];

    void init(int size) {
        for(int i = 0;i <= size;i++) father[i] = i;
    }

    int getFather(int now) {
        if(father[now] == now) return now;
        father[now] = getFather(father[now]);
        return father[now];
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

    void merge(int u,int v) {
        u = getFather(u); v = getFather(v);
        if(u == v) return;
        father[u] = v;
    }
} bcset;

struct Edge {
    int u,v,w;

    Edge() : u(0) , v(0) , w(0) { }

    Edge(int u,int v,int w) : u(u) , v(v) , w(w) { }

    bool operator < (const Edge &otherEdge) const {
        return w > otherEdge.w;
    }
} edges[MAXM];

int n,m,fathers[MAXN][MAX_DEPTH + 1],minWeight[MAXN][MAX_DEPTH + 1],depths[MAXN];

void getInfo(int now,int father,int weight) {
    fathers[now][0] = father;
    minWeight[now][0] = weight;
    depths[now] = depths[father] + 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
        minWeight[now][i] = min(minWeight[now][i - 1],minWeight[fathers[now][i - 1]][i - 1]);
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now,tmpEdge.weight);
    }
}

int getMinValue(int u,int v) {
    if(u == v) return 0;
    int result = INF;
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            result = min(result,minWeight[u][i]);
            u = fathers[u][i];
        }
    }
    if(u == v) return result;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            result = min(result,minWeight[u][i]);
            result = min(result,minWeight[v][i]);
            u = fathers[u][i];
            v = fathers[v][i];
        }
    }
    result = min(result,minWeight[u][0]);
    result = min(result,minWeight[v][0]);
    return result;
}

int main() {
    n = read<int>(),m = read<int>();
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        edges[i] = Edge(u,v,w);
    }
    sort(edges,edges + m);
    bcset.init(n);
    for(int i = 0;i < m;i++) {
        Edge &tmpEdge = edges[i];
        if(!bcset.isLinked(tmpEdge.u,tmpEdge.v)) {
            bcset.merge(tmpEdge.u,tmpEdge.v);
            graph.addEdge(tmpEdge.u,tmpEdge.v,tmpEdge.w);
            graph.addEdge(tmpEdge.v,tmpEdge.u,tmpEdge.w);
        }
    }
    for(int i = 0;i <= MAX_DEPTH;i++) {
        minWeight[0][i] = INF;
    }
    for(int i = 1;i <= n;i++) {
        if(depths[i] == 0) {
            getInfo(i,0,INF);
        }
    }
    int q = read<int>();
    while(q--) {
        int x = read<int>(),y = read<int>();
        if(!bcset.isLinked(x,y)) {
            printf("%d\n",-1);
        }else {
            printf("%d\n",getMinValue(x,y));
        }
    }
    return 0;
}
