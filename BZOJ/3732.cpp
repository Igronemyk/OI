#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 15010;
const int MAXM = 30010;
const int MAX_DEPTH = 14;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXN * 2];
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

struct Edge {
    int u,v,w;
    
    bool operator < (const Edge &otherEdge) const {
        return w < otherEdge.w;
    }
} edges[MAXM];

struct BCS {
    int fathers[MAXN];

    void init(int size) {
        for(int i = 1;i <= size;i++) fathers[i] = i;
    }

    int getFather(int now) {
        if(now == fathers[now]) return now;
        fathers[now] = getFather(fathers[now]);
        return fathers[now];
    }

    void merge(int u,int v) {
        u = getFather(u);
        v = getFather(v);
        if(u == v) return;
        fathers[u] = v;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
} bcset;

int maxDis[MAXN][MAX_DEPTH + 1];

int fathers[MAXN][MAX_DEPTH + 1],depths[MAXN];


void getInfo(int now,int father,int weight) {
    maxDis[now][0] = weight;
    fathers[now][0] = father;
    depths[now] = depths[father] + 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
        maxDis[now][i] = max(maxDis[now][i - 1],maxDis[fathers[now][i - 1]][i - 1]);
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now,tmpEdge.weight);
    }
}

int getMaxDis(int u,int v) {
    if(u == v) return 0;
    int result = 0;
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            result = max(result,maxDis[u][i]);
            u = fathers[u][i];
        }
    }
    if(u == v) return result;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            result = max(result,maxDis[u][i]);
            u = fathers[u][i];
            result = max(result,maxDis[v][i]);
            v = fathers[v][i];
        }
    }
    result = max(result,maxDis[u][0]);
    result = max(result,maxDis[v][0]);
    return result;
}

int main() {
    int N = read<int>(),M = read<int>(),K = read<int>();
    bcset.init(N);
    for(int i = 0;i < M;i++) {
        edges[i].u = read<int>(); edges[i].v = read<int>(); edges[i].w = read<int>();
    }
    sort(edges,edges + M);
    for(int i = 0;i < M;i++) {
        Edge &tmpEdge = edges[i];
        if(!bcset.isLinked(tmpEdge.u,tmpEdge.v)) {
            graph.addEdge(tmpEdge.u,tmpEdge.v,tmpEdge.w);
            graph.addEdge(tmpEdge.v,tmpEdge.u,tmpEdge.w);
            bcset.merge(tmpEdge.u,tmpEdge.v);
        }
    }
    getInfo(1,0,0);
    while(K--) {
        int A = read<int>(),B = read<int>();
        printf("%d\n",getMaxDis(A,B));
    }
    return 0;
}
