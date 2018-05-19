#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

const int MAXM = 10010;
const int MAXN = 1010;
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

int n,m;

int dis[MAXN],cnt[MAXN];
bool visit[MAXN],canVisit[MAXN];

void dfs(int now) {
    if(now == n) {
        canVisit[now] = true;
        return;
    }
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.weight < 0) continue;
        if(!visit[tmpEdge.to]) {
            dfs(tmpEdge.to);
        }
        if(canVisit[tmpEdge.to]) {
            canVisit[now] = true;
        }
    }
}

bool spfa(int start) {
    queue<int> que;
    for(int i = 1;i <= n;i++) dis[i] = -INF;
    que.push(start);
    dis[start] = 0;
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(!canVisit[tmpEdge.to]) continue;
            if(dis[tmpEdge.to] >= dis[now] + tmpEdge.weight) continue;
            dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
            if(!visit[tmpEdge.to]) {
                visit[tmpEdge.to] = true;
                que.push(tmpEdge.to);
                cnt[tmpEdge.to]++;
                if(cnt[tmpEdge.to] > n) {
                    return false;
                }
            }
        }
    }
    return true;
}

pair<int,int> values[MAXM];

int main() {
    n = read<int>(); m = read<int>();
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v,1);
        graph.addEdge(v,u,-2);
        values[i] = make_pair(u,v);
    }
    dfs(1);
    memset(visit,0,sizeof(visit));
    bool result = spfa(1);
    if(result) {
        printf("Yes\n");
        for(int i = 0;i < m;i++) {
            pair<int,int> &tmpValue = values[i];
            if(!canVisit[tmpValue.second] || !canVisit[tmpValue.first]) {
                printf("%d\n",1);
            }else {
                printf("%d\n",dis[tmpValue.second] - dis[tmpValue.first]);
            }
        }
    }else {
        printf("No\n");
    }
    return 0;
}
