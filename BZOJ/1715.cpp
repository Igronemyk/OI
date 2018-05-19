#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 510;
const int MAXM = 6100;

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
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
} graph;

int dis[MAXN];
bool visit[MAXN],found;


void spfa(int now) {
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dis[tmpEdge.to] <= dis[now] + tmpEdge.weight) continue;
        if(visit[tmpEdge.to]) {
            found = true;
            return;
        }
        dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
        spfa(tmpEdge.to);
        if(found) return;
    }
    visit[now] = false;
}

void init() {
    graph.clear();
    memset(dis,0,sizeof(dis));
    memset(visit,0,sizeof(visit));
    found = false;
}

int main() {
    int F = read<int>();
    while(F--) {
        init();
        int N = read<int>(),M = read<int>(),W = read<int>();
        for(int i = 0;i < M;i++) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            graph.addEdge(u,v,w);
            graph.addEdge(v,u,w);
        }
        for(int i = 0;i < W;i++) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            graph.addEdge(u,v,-w);
        }
        for(int i = 1;i <= N;i++) {
            spfa(i);
            if(found) {
                break;
            }
        }
        if(found) {
            printf("YES\n");
        }else {
            printf("NO\n");
        }
    }
    return 0;
}
