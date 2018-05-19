#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 5e4 + 10;
const int MAXM = 1e7;

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
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v) {
        addEdge(u,v);
        addEdge(v,u);
    }
} graph;

int que[MAXN * 2],f[MAXN],values[MAXN * 2],fathers[MAXN],dfn[MAXN],low[MAXN],nowTime,result;

void dp(int root,int start) {
    int nowIndex = 0,now = start;
    while(now != root) {
        values[++nowIndex] = f[now];
        now = fathers[now];
    }
    values[++nowIndex] = f[root];
    for(int i = 1;i <= nowIndex;i++) {
        values[nowIndex + i] = values[i];
    }
    int mid = nowIndex / 2,left = 1,right = 0;
    nowIndex *= 2;
    for(int i = 1;i <= nowIndex;i++) {
        while(left <= right && i - que[left] > mid) {
            left++;
        }
        if(left <= right) {
            result = max(result,values[que[left]] + values[i] + i - que[left]);
        }
        while(left <= right && values[i] - i >= values[que[right]] - que[right]) {
            right--;
        }
        que[++right] = i;
    }
    nowIndex /= 2;
    for(int i = 1;i <= nowIndex;i++) {
        f[root] = max(f[root],values[i] + min(nowIndex - i,i));
    }
}

void tarjan(int now) {
    dfn[now] = ++nowTime;
    low[now] = nowTime;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == fathers[now]) continue;
        if(!dfn[tmpEdge.to]) {
            fathers[tmpEdge.to] = now;
            tarjan(tmpEdge.to);
        }
        low[now] = min(low[now],low[tmpEdge.to]);
        if(low[tmpEdge.to] > dfn[now]) {
            result = max(result,f[tmpEdge.to] + f[now] + 1);
            f[now] = max(f[now],f[tmpEdge.to] + 1);
        }
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == fathers[now] || fathers[tmpEdge.to] == now || dfn[tmpEdge.to] <= dfn[now]) continue;
        dp(now,tmpEdge.to); 
    }
}

int main() {
    read<int>();
    int m = read<int>();
    for(int i = 0;i < m;i++) {
        int k = read<int>(),u = read<int>();
        for(int j = 1;j < k;j++) {
            int v = read<int>();
            graph.addTwoEdges(u,v);
            u = v;
        }
    }
    tarjan(1);
    printf("%d\n",result);
    return 0;
}
