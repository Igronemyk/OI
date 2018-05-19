#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 2000010;
const int MAXN = 1000010;
const int MAX_DEPTH = 20;
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

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v) {
        addEdge(u,v);
        addEdge(v,u);
    }

    void clear() {
        tot = 0;
    }

    void resetHead(int now) {
        heads[now] = -1;
    }
} graph,virtualGraph;

int fathers[MAXN][MAX_DEPTH + 1],depths[MAXN],dfn[MAXN],selectNode[MAXN],stk[MAXN],k,nowTime;
int minWeight[MAXN],maxWeight[MAXN],sizes[MAXN],minResult,maxResult;

long long sumResult,sumWeight[MAXN];

bool visit[MAXN];

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

int getDisSpecial(int u,int v) {
    return depths[v] - depths[u];
}

bool comp(const int &a,const int &b) {
    return dfn[a] < dfn[b];
}

void build() {
    sort(selectNode,selectNode + k,comp);
    int top = 0;
    stk[++top] = 1;
    for(int i = 0;i < k;i++) {
        int now = selectNode[i],lca = getLCA(stk[top],now);
        if(now == 1) continue;
        if(lca != stk[top]) {
            while(true) {
                if(depths[stk[top - 1]] <= depths[lca]) {
                    virtualGraph.addEdge(lca,stk[top],getDisSpecial(lca,stk[top]));
                    top--;
                    if(lca != stk[top]) {
                        stk[++top] = lca;
                    }
                    if(now != stk[top]) {
                        stk[++top] = now;
                    }
                    break;
                }
                virtualGraph.addEdge(stk[top - 1],stk[top],getDisSpecial(stk[top - 1],stk[top]));
                top--;
            }
        }else {
            if(now != stk[top]) {
                stk[++top] = now;
            }
        }
    }
    top--;
    for(;top > 0;top--) {
        virtualGraph.addEdge(stk[top],stk[top + 1],getDisSpecial(stk[top],stk[top + 1]));
    }
}

void dp(int now,int father) {
    minWeight[now] = visit[now] ? 0 : INF;
    maxWeight[now] = visit[now] ? 0 : -INF;
    sizes[now] = visit[now] ? 1 : 0;
    sumWeight[now] = 0;
    int firstMax = visit[now] ? 0 : -INF,secondMax = -INF,firstMin = visit[now] ? 0 : INF,secondMin = INF;
    for(int i = virtualGraph.heads[now];i != -1;i = virtualGraph.edges[i].next) {
        Graph::Edge &tmpEdge = virtualGraph.edges[i];
        dp(tmpEdge.to,now);
        sumResult += (sumWeight[now] + sizes[now] * 1LL * tmpEdge.weight) * 1LL * sizes[tmpEdge.to] + sumWeight[tmpEdge.to] * sizes[now];
        sumWeight[now] += sizes[tmpEdge.to] * 1LL * tmpEdge.weight + sumWeight[tmpEdge.to];
        sizes[now] += sizes[tmpEdge.to];
        int tmpMin = minWeight[tmpEdge.to] + tmpEdge.weight,tmpMax = maxWeight[tmpEdge.to] + tmpEdge.weight;
        minWeight[now] = min(minWeight[now],tmpMin);
        maxWeight[now] = max(maxWeight[now],tmpMax);
        if(tmpMin < firstMin) {
            secondMin = firstMin;
            firstMin = tmpMin;
        }else if(tmpMin < secondMin) {
            secondMin = tmpMin;
        }
        if(tmpMax > firstMax) {
            secondMax = firstMax;
            firstMax = tmpMax;
        }else if(tmpMax > secondMax) {
            secondMax = tmpMax;
        }
    }
    virtualGraph.resetHead(now);
    maxResult = max(maxResult,firstMax + secondMax);
    minResult = min(minResult,firstMin + secondMin);
}

void solve() {
    k = read<int>();
    for(int i = 0;i < k;i++) {
        selectNode[i] = read<int>();
        visit[selectNode[i]] = true;
    }
    sumResult = 0;
    minResult = INF;
    maxResult = -INF;
    build();
    virtualGraph.clear();
    dp(1,0);
    printf("%lld %d %d\n",sumResult,minResult,maxResult);
    for(int i = 0;i < k;i++) {
        visit[selectNode[i]] = false;
    }
}

void getInfo(int now,int father) {
    fathers[now][0] = father;
    dfn[now] = ++nowTime;
    depths[now] = depths[father] + 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now);
    }
}

int main() {
    int n = read<int>();
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    getInfo(1,0);
    int q = read<int>();
    while(q--) {
        solve();
    }
    return 0;
}
