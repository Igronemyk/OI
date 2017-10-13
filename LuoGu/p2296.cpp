#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 200010;

template<typename T>
inline T read() {
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

namespace Adj {
    struct Node {
        int to,next;
    } nodes[MAXM];
    int tot,heads[MAXN];

    void init() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }
}

using namespace Adj;

void dfs(int now,bool *visit) {
    visit[now] = true;
    for(int i = heads[now];i != -1;i = nodes[i].next) {
        if(!visit[nodes[i].to]) dfs(nodes[i].to,visit);
    }
}

struct Edge {
    int to,weight;
    Edge() : to(-1) , weight(-1) {}
    Edge(int to,int weight) : to(to) , weight(weight) {}
    bool operator < (const Edge otherEdge) const {
        return this->weight > otherEdge.weight;
    }
};

int * dijkstra(int nodeSize,int start,bool *forbidden) {
    int *dis = new int[nodeSize];
    memset(dis,INF,sizeof(int) * nodeSize);
    bool *visit = new bool[nodeSize];
    memset(visit,false,sizeof(bool) * nodeSize);
    if(forbidden[start]) return dis;
    priority_queue<Edge> pq;
    dis[start] = 0;
    pq.push(Edge(start,0));
    int doingTimes = 0;
    while(!pq.empty() && doingTimes <= nodeSize) {
        Edge tmpEdge = pq.top();
        pq.pop();
        if(visit[tmpEdge.to]) continue;
        visit[tmpEdge.to] = true;
        for(int i = heads[tmpEdge.to];i != -1;i = nodes[i].next) {
            if(!visit[nodes[i].to] && !forbidden[nodes[i].to] && dis[nodes[i].to] > dis[tmpEdge.to] + 1){
                dis[nodes[i].to] = dis[tmpEdge.to] + 1;
                pq.push(Edge(nodes[i].to,dis[nodes[i].to]));
            }
        }
        doingTimes++;
    }
    return dis;
}

struct Data{
    int u,v;
    Data() : u(-1) , v(-1) {}
    Data(int u,int v) : u(u) , v(v) {}
};

int main() {
    int n = read<int>(), m = read<int>();
    init();
    Data *datas = new Data[m];
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        u--;v--;
        addEdge(v,u);
        datas[i] = Data(u,v);
    }
    int s = read<int>(),t = read<int>();
    s--;t--;
    bool *visit = new bool[n];
    memset(visit,false,sizeof(bool) * n);
    dfs(t,visit);
    bool *forbidden = new bool[n];
    memset(forbidden,false,sizeof(bool) * n);
    for(int i = 0;i < n;i++) {
        if(visit[i]) continue;
        forbidden[i] = true;
        for(int j = heads[i];j != -1;j = nodes[j].next) {
            forbidden[nodes[j].to] = true;
        }
    }
    init();
    for(int i = 0;i < m;i++){
        addEdge(datas[i].u,datas[i].v);
    }
    int *dis = dijkstra(n,s,forbidden);
    printf("%d\n",dis[t] == INF ? -1 : dis[t]);
    return 0;
}
