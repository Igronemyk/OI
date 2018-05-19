#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 10010;
const int MAXM = 20010;

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

int main() {
    int n = read<int>(),m = read<int>();
    for(int i = 0;i < m;i++) {
        int type = read<int>(),a = read<int>(),b = read<int>();
        if(type == 1) {
            int c = read<int>();
            graph.addEdge(a,b,-c);
        }else if(type == 2) {
            int c = read<int>();
            graph.addEdge(b,a,c);
        }else {
            graph.addEdge(a,b,0);
            graph.addEdge(b,a,0);
        }
    }
    for(int i = 1;i <= n;i++) {
        spfa(i);
        if(found) break;
    }
    if(found) {
        printf("No\n");
    }else {
        printf("Yes\n");
    }
    return 0;
}
