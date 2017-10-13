#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 3000010;
const int MAXM = 3000010;

template<typename T>
inline T read() {
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

namespace Adj {
    struct Node {
        int to,weight,next;
    } nodes[MAXM];
    int tot,heads[MAXN];

    void init() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        nodes[tot].to = v;
        nodes[tot].weight = w;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }
}

using namespace Adj;

struct Edge {
    int to,weight;
    Edge() : to(-1) , weight(-1) {}
    Edge(int to,int weight) : to(to) , weight(weight) {}
    bool operator < (const Edge otherEdge) const {
        return this->weight > otherEdge.weight;
    }
};


int * dijkstra(int nodeSize,int start,int end) {
    int *dis = new int[nodeSize];
    memset(dis,INF,sizeof(int) * nodeSize);
    bool *visit = new bool[nodeSize];
    memset(visit,false,sizeof(bool) * nodeSize);
    priority_queue<Edge> pq;
    dis[start] = 0;
    pq.push(Edge(start,0));
    int doingTimes = 0;
    while(!pq.empty() && doingTimes <= nodeSize) {
        Edge tmpEdge = pq.top();
        pq.pop();
        if(visit[tmpEdge.to]) continue;
        if(tmpEdge.to == end) return dis;
        visit[tmpEdge.to] = true;
        for(int i = heads[tmpEdge.to];i != -1;i = nodes[i].next) {
            if(!visit[nodes[i].to] && dis[nodes[i].to] > dis[tmpEdge.to] + nodes[i].weight){
                dis[nodes[i].to] = dis[tmpEdge.to] + nodes[i].weight;
                pq.push(Edge(nodes[i].to,dis[nodes[i].to]));
            }
        }
        doingTimes++;
    }
    return dis;
}

int main(){
    int n = read<int>(),m = read<int>(),T = read<int>();
    init();
    for(int i = 0;i < m;i++){
        int x = read<int>(),y = read<int>(),v = read<int>();
        x--;y--;
        addEdge(x,y,v);
        addEdge(y,x,v);
    }
    int *result = dijkstra(n,0,T - 1);
    printf("%d\n",result[T - 1]);
    return 0;
}
