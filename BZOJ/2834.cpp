#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <cmath>

using namespace std;

const int MAXM = 800010;
const int MAXN = 200010;
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

int dis[MAXN];
bool visit[MAXN];

void spfa(int S) {
    queue<int> que;
    que.push(S);
    memset(dis,INF,sizeof(dis));
    memset(visit,false,sizeof(visit));
    visit[S] = true;
    dis[S] = 0;
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[now] + tmpEdge.weight >= dis[tmpEdge.to]) continue;
            dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
            if(!visit[tmpEdge.to]) {
                visit[tmpEdge.to] = true;
                que.push(tmpEdge.to);
            }
        }
    }
}

struct Data {
    int x,y,id;

    Data() : x(0) , y(0) , id(0) { }

    Data(int x,int y,int id) : x(x) , y(y) , id(id) { }
} datas[MAXN];

bool comp1(const Data &a,const Data &b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool comp2(const Data &a,const Data &b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    int n = read<int>(),m = read<int>(),S = m,T = m + 1;
    for(int i = 0;i < m + 2;i++) {
        int x = read<int>(),y = read<int>();
        datas[i] = Data(x,y,i);
    }
    for(int i = 0;i < m;i++) {
        graph.addTwoEdges(2 * i,2 * i + 1,1);
    }
    sort(datas,datas + m + 2,comp1);
    for(int i = 1;i < m + 2;i++) {
        if(datas[i].x == datas[i - 1].x) {
            graph.addTwoEdges(2 * datas[i].id,2 * datas[i - 1].id,2 * (datas[i].y - datas[i - 1].y));
        }
    }
    sort(datas,datas + m + 2,comp2);
    for(int i = 1;i < m + 2;i++) {
        if(datas[i].y == datas[i - 1].y) {
            graph.addTwoEdges(2 * datas[i].id + 1,2 * datas[i - 1].id + 1,2 * (datas[i].x - datas[i - 1].x));
        }
    }
    S *= 2;
    T *= 2;
    graph.addTwoEdges(S,S + 1,0);
    graph.addTwoEdges(T,T + 1,0);
    spfa(S);
    if(dis[T] == INF) {
        printf("-1\n");
    }else {
        printf("%d\n",dis[T]);
    }
    return 0;
}
