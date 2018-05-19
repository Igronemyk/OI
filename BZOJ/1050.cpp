#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <queue>

using namespace std;

const int MAXN = 510;
const int MAXM = 10010;
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

int dis[MAXN];
bool visit[MAXN];

queue<int> que;

void spfa() {
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[tmpEdge.to] <= max(dis[now],tmpEdge.weight)) continue;
            dis[tmpEdge.to] = max(dis[now],tmpEdge.weight);
            if(!visit[tmpEdge.to]) {
                visit[tmpEdge.to] = true;
                que.push(tmpEdge.to);
            }
        }
    }
}

typedef pair<pair<int,int>,int > Edge;

Edge edges[MAXM];

bool comp(const Edge &a,const Edge &b) {
    return a.second > b.second;
}

int main() {
    int N = read<int>(),M = read<int>();
    for(int i = 0;i < M;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        edges[i] = make_pair(make_pair(u,v),w);
    }
    sort(edges,edges + M,comp);
    int S = read<int>(),T = read<int>();
    memset(dis,INF,sizeof(dis));
    dis[S] = 0;
    double result = INF;
    int maxValue = -1,minValue = -1;
    for(int i = 0;i < M;i++) {
        Edge &tmpEdge = edges[i];
        int u = tmpEdge.first.first,v = tmpEdge.first.second;
        graph.addEdge(u,v,tmpEdge.second);
        graph.addEdge(v,u,tmpEdge.second);
        if(dis[u] > dis[v]) swap(u,v);
        if(max(dis[u],tmpEdge.second) < dis[v]) {
            dis[v] = max(dis[u],tmpEdge.second);
            visit[v] = true;
            que.push(v);
            spfa();
        }
        if(dis[T] != INF) {
            double tmpResult = dis[T] * 1.00 / tmpEdge.second;
            if(tmpResult < result) {
                result = tmpResult;
                maxValue = dis[T];
                minValue =  tmpEdge.second;
            }
        }
    }
    if(maxValue == -1 && minValue == -1) {
        printf("IMPOSSIBLE\n");
    }else {
        int gcdValue = __gcd(maxValue,minValue);
        if(minValue / gcdValue == 1) {
            printf("%d\n",maxValue / gcdValue);
        }else {
            printf("%d/%d\n",maxValue / gcdValue,minValue / gcdValue);
        }
    }
    return 0;
}
