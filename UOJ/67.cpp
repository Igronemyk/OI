#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 2e5 + 10;
const int MAXN = 1e5 + 10;

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
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() :tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

int dfn[MAXN],low[MAXN],nowIndex;
bool isCut[MAXN];

void tarjan(int now,int father) {
    low[now] = dfn[now] = ++nowIndex;
    int child = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        if(!dfn[tmpEdge.to]) {
            tarjan(tmpEdge.to,now);
            low[now] = min(low[now],low[tmpEdge.to]);
            if(father != 0 && low[tmpEdge.to] >= dfn[now] && !isCut[now]) {
                isCut[now] = true;
            }
            child++;
        }else {
            low[now] = min(low[now],dfn[tmpEdge.to]);
        }
    }
    if(father == 0 && child > 1 && !isCut[now]) {
        isCut[now] = true;
    }
}

int result[MAXN],resultCnt,degree[MAXN];

int main() {
    int n = read<int>(),m = read<int>();
    for(int i = 1;i <= m;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
        degree[u]++;
        degree[v]++;
    }
    tarjan(1,0);
    for(int i = 1;i <= n;i++) {
        if(isCut[i]) continue;
        if(degree[i] == m - (n - 2)) {
            result[resultCnt++] = i;
        }
    }
    printf("%d\n",resultCnt);
    for(int i = 0;i < resultCnt;i++) {
        printf("%d ",result[i]);
    }
    printf("\n");
    return 0;
}
