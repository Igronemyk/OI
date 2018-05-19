#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 500010;
const int MAX_DEPTH = 19;

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
    Edge edges[MAXN * 2];
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

int depths[MAXN],fathers[MAXN][MAX_DEPTH + 1];

void getInfo(int now,int father) {
    depths[now] = depths[father] + 1;
    fathers[now][0] = father;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now);
    }
}

int getLCA(int u,int v) {
    if(u == v) return u;
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            u = fathers[u][i];
        }
    }
    if(u == v) return u;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            u = fathers[u][i];
            v = fathers[v][i];
        }
    }
    return fathers[u][0];
}

int getDis(int u,int v) {
    return depths[u] + depths[v] - 2 * depths[getLCA(u,v)];
}

int main() {
    int N = read<int>(),M = read<int>();
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    getInfo(1,0);
    while(M--) {
        int x = read<int>(),y = read<int>(),z = read<int>();
        int result = MAXN * 3,sign = -1;
        {
            int lca = getLCA(x,y);
            int tmpResult = depths[x] - depths[lca] + depths[y] - depths[lca];
            tmpResult += getDis(lca,z);
            if(tmpResult < result) {
                result = tmpResult;
                sign = lca;
            }
        }
        {
            int lca = getLCA(y,z);
            int tmpResult = depths[y] - depths[lca] + depths[z] - depths[lca];
            tmpResult += getDis(x,lca);
            if(tmpResult < result) {
                result = tmpResult;
                sign = lca;
            }
        }
        {
            int lca = getLCA(x,z);
            int tmpResult = depths[x] - depths[lca] + depths[z] - depths[lca];
            tmpResult += getDis(y,lca);
            if(tmpResult < result) {
                result = tmpResult;
                sign = lca;
            }
        }
        printf("%d %d\n",sign,result);
    }
    return 0;
}
