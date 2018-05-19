#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <climits>

using namespace std;

const int MAXM = 500010;
const int MAXN = 250010;
const int MAX_DEPTH = 19;
const long long INF = 0x3f3f3f3f3f3f3f3f;

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
        long long weight;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,long long w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v,long long w) {
        addEdge(u,v,w);
        addEdge(v,u,w);
    }

    void clear() {
        tot = 0;
    }

    void resetHead(int now) {
        heads[now] = -1;
    }

} graph,virtualGraph;

int n,fathers[MAXN][MAX_DEPTH + 1],depths[MAXN],dfn[MAXN],nowTime,selectNode[MAXN],stk[MAXN];
long long minWeight[MAXN][MAX_DEPTH + 1];

void getInfo(int now,int father,long long weight) {
    dfn[now] = ++nowTime;
    depths[now] = depths[father] + 1;
    fathers[now][0] = father;
    minWeight[now][0] = weight;
    for(int i = 1;i <+ MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
        minWeight[now][i] = min(minWeight[now][i - 1],minWeight[fathers[now][i - 1]][i - 1]);
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now,tmpEdge.weight);
    }
}

bool comp(const int &a,const int &b) {
    return dfn[a] < dfn[b];
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

long long getMinValue(int u,int v) {
    if(u == v) return 0;
    long long result = INF;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            result = min(result,minWeight[u][i]);
            u = fathers[u][i];
        }
    }
    return result;
}

bool visit[MAXN];
long long dp[MAXN];

void dfs(int now,long long weight) {
    long long result = 0;
    dp[now] = weight;
    for(int i = virtualGraph.heads[now];i != -1;i = virtualGraph.edges[i].next) {
        Graph::Edge &tmpEdge = virtualGraph.edges[i];
        if(visit[tmpEdge.to]) {
            result += tmpEdge.weight;
        }else {
            dfs(tmpEdge.to,tmpEdge.weight);
            result += dp[tmpEdge.to];
        }
        dfs(tmpEdge.to,tmpEdge.weight);
    }
    virtualGraph.resetHead(now);
    if(result == 0) {
        result = INF;
    }
    dp[now] = min(dp[now],result);
}

void solve(int k) {
    for(int i = 0;i < k;i++) {
        selectNode[i] = read<int>();
        visit[selectNode[i]] = true;
    }
    sort(selectNode,selectNode + k,comp);
    int top = 0;
    stk[++top] = 1;
    virtualGraph.clear();
    for(int i = 0;i < k;i++) {
        int now = selectNode[i],lca = getLCA(stk[top],now);
        if(stk[top] != lca) {
            while(true) {
                if(depths[stk[top - 1]] <= depths[lca]) {
                    virtualGraph.addEdge(lca,stk[top],getMinValue(stk[top],lca));
                    top--;
                    if(stk[top] != lca) {
                        stk[++top] = lca;
                    }
                    if(stk[top] != now) {
                        stk[++top] = now;
                    }
                    break;
                }
                virtualGraph.addEdge(stk[top - 1],stk[top],getMinValue(stk[top],stk[top - 1]));
                top--;
            }
        }else {
            if(stk[top] != now) {
                stk[++top] = now;
            }
        }
    }
    top--;
    for(;top > 0;top--) {
        virtualGraph.addEdge(stk[top],stk[top + 1],getMinValue(stk[top + 1],stk[top]));
    }
    dfs(1,INF);
    printf("%lld\n",dp[1]);
    for(int i = 0;i < k;i++) {
        visit[selectNode[i]] = false;
    }
}

int main() {
    n = read<int>();
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addTwoEdges(u,v,w);
    }
    for(int i = 0;i <= MAX_DEPTH;i++) {
        minWeight[0][i] = INF;
    }
    getInfo(1,0,INF);
    int m = read<int>();
    while(m--) {
        int k = read<int>();
        solve(k);
    }
    return 0;
}
