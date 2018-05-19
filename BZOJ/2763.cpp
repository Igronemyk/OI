#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 10010;
const int MAXM = 100010;
const int MAXK = 11;
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

    void addTwoEdges(int u,int v,int w) {
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
} graph;

int n,m,k,dis[MAXN][MAXK];
bool visit[MAXN];

void spfa(int S) {
    memset(dis,INF,sizeof(dis));
    memset(visit,false,sizeof(visit));
    queue<int> que;
    que.push(S);
    for(int i = 0;i <= k;i++) {
        dis[S][i] = 0;
    }
    visit[S] = true;
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int nowK = 0;nowK <= k;nowK++) {
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(dis[now][nowK] + tmpEdge.weight >= dis[tmpEdge.to][nowK]) continue;
                dis[tmpEdge.to][nowK] = dis[now][nowK] + tmpEdge.weight;
                if(!visit[tmpEdge.to]) {
                    visit[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
            if(nowK == k) continue;
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(dis[now][nowK] >= dis[tmpEdge.to][nowK + 1]) continue;
                dis[tmpEdge.to][nowK + 1] = dis[now][nowK];
                if(!visit[tmpEdge.to]) {
                    visit[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }

        }
    }
}

int main() {
    n = read<int>(); m = read<int>(); k = read<int>();
    int s = read<int>(),t = read<int>();
    for(int i = 0;i < m;i++) {
        int a = read<int>(),b = read<int>(),c = read<int>();
        graph.addTwoEdges(a,b,c);
    }
    spfa(s);
    printf("%d\n",dis[t][k]);
    return 0;
}
