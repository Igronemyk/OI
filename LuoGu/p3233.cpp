#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXM = 600010;
const int MAXN = 300010;
const int MAX_DEPTH = 19;
const int INF = 0x3f3f3f3f;

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

int fathers[MAXN][MAX_DEPTH + 1],selectNode[MAXN],tmpNode[MAXN],dfn[MAXN],depths[MAXN],stk[MAXN],belong[MAXN],dis[MAXN],sizes[MAXN],results[MAXN],k,nowTime;
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

int getDis(int u,int v) {
    return depths[u] + depths[v] - 2 * depths[getLCA(u,v)];
}

int jumpTo(int u,int dis) {
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(dis >= (1 << i)) {
            dis -= (1 << i);
            u = fathers[u][i];
        }
    }
    return u;
}

bool comp(const int &a,const int &b) {
    return dfn[a] < dfn[b];
}

void build() {
    sort(selectNode,selectNode + k,comp);
    virtualGraph.clear();
    int top = 0;
    stk[++top] = 1;
    for(int i = 0;i < k;i++) {
        int now = selectNode[i],lca = getLCA(stk[top],now);
        if(now == 1) continue;
        if(lca != stk[top]) {
            while(true) {
                if(depths[stk[top - 1]] <= depths[lca]) {
                    virtualGraph.addEdge(lca,stk[top]);
                    top--;
                    if(lca != stk[top]) {
                        stk[++top] = lca;
                    }
                    if(now != stk[top]) {
                        stk[++top] = now;
                    }
                    break;
                }
                virtualGraph.addEdge(stk[top - 1],stk[top]);
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
        virtualGraph.addEdge(stk[top],stk[top + 1]);
    }
}

void dfsFirst(int now,int father) {
    if(visit[now]) {
        belong[now] = now;
        dis[now] = 0;
    }else {
        dis[now] = INF;
    }
    for(int i = virtualGraph.heads[now];i != -1;i = virtualGraph.edges[i].next) {
        Graph::Edge &tmpEdge = virtualGraph.edges[i];
        int childDis = depths[tmpEdge.to] - depths[now];
        dfsFirst(tmpEdge.to,now);
        if(dis[now] > dis[tmpEdge.to] + childDis) {
            dis[now] = dis[tmpEdge.to] + childDis;
            belong[now] = belong[tmpEdge.to];
        }else if(dis[now] == dis[tmpEdge.to] + childDis && belong[tmpEdge.to] < belong[now]) {
            belong[now] = belong[tmpEdge.to];
        }
    }
}

void dfsSecond(int now,int father) {
    for(int i = virtualGraph.heads[now];i != -1;i = virtualGraph.edges[i].next) {
        Graph::Edge &tmpEdge = virtualGraph.edges[i];
        int childDis = depths[tmpEdge.to] - depths[now];
        if(dis[now] + childDis < dis[tmpEdge.to]) {
            dis[tmpEdge.to] = dis[now] + childDis;
            belong[tmpEdge.to] = belong[now];
        }else if(dis[now] + childDis == dis[tmpEdge.to] && belong[now] < belong[tmpEdge.to]) {
            belong[tmpEdge.to] = belong[now];
        }
        dfsSecond(tmpEdge.to,now);
    }
    results[belong[now]] = max(results[belong[now]],sizes[now]);
}

void dfsThird(int now,int father) {
    for(int i = virtualGraph.heads[now];i != -1;i = virtualGraph.edges[i].next) {
        Graph::Edge &tmpEdge = virtualGraph.edges[i];
        if(belong[tmpEdge.to] != belong[now]) {
            int nowDis = getDis(belong[tmpEdge.to],belong[now]),cutPoint = 0;
            if(nowDis & 1) {
                cutPoint = jumpTo(tmpEdge.to,nowDis / 2 - dis[tmpEdge.to]);
            }else {
                cutPoint = jumpTo(tmpEdge.to,nowDis / 2 - dis[tmpEdge.to]);
                if(cutPoint != tmpEdge.to && cutPoint != now) {
                    cutPoint = jumpTo(tmpEdge.to,nowDis / 2 - dis[tmpEdge.to] - (belong[now] < belong[tmpEdge.to]));
                }else if(cutPoint == now) {
                    cutPoint = jumpTo(tmpEdge.to,nowDis / 2 - dis[tmpEdge.to] - 1);
                }
            }
            results[belong[now]] -= sizes[cutPoint];
            results[belong[tmpEdge.to]] += sizes[cutPoint] - sizes[tmpEdge.to];
        }
        dfsThird(tmpEdge.to,now);
    }
    virtualGraph.resetHead(now);
}

void getInfo(int now,int father) {
    fathers[now][0] = father;
    dfn[now] = ++nowTime;
    depths[now] = depths[father] + 1;
    sizes[now] = 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now);
        sizes[now] += sizes[tmpEdge.to];
    }
}

void solve() {
    k = read<int>();
    for(int i = 0;i < k;i++) {
        selectNode[i] = read<int>();
        tmpNode[i] = selectNode[i];
        visit[selectNode[i]] = true;
        results[selectNode[i]] = 0;
    }
    build();
    dfsFirst(1,0);
    dfsSecond(1,0);
    dfsThird(1,0);
    for(int i = 0;i < k;i++) {
        printf("%d ",results[tmpNode[i]]);
        visit[selectNode[i]] = false;
    }
    printf("\n");
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
