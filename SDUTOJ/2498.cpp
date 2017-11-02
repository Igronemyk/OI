#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <stack>

using namespace std;

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
    } *edges;
    int tot,*heads;
    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }
};

struct Edge {
    int to,weight;
    Edge() : to(-1) , weight(-1) { }
    Edge(int to,int weight) : to(to) , weight(weight) { }
    bool operator < (const Edge otherEdge) const {
        return this->weight < otherEdge.weight;
    }
};


void dijkstra(Graph &graph,int n,int start,int *dis,int *prev) {
    memset(dis,-INF,sizeof(int) * n);
    bool *vis = new bool[n];
    memset(vis,false,sizeof(bool) * n);
    memset(prev,INF,sizeof(int) * n);
    priority_queue<Edge> que;
    que.push(Edge(start,0));
    dis[start] = 0;
    while(!que.empty()) {
        Edge tmpEdge = que.top();
        que.pop();
        if(vis[tmpEdge.to]) continue;
        vis[tmpEdge.to] = true;
        for(int i = graph.heads[tmpEdge.to];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpUpdateEdge = graph.edges[i];
            if(dis[tmpUpdateEdge.to] < dis[tmpEdge.to] + tmpUpdateEdge.weight) {
                dis[tmpUpdateEdge.to] = dis[tmpEdge.to] + tmpUpdateEdge.weight;
                prev[tmpUpdateEdge.to] = tmpEdge.to;
                que.push(Edge(tmpUpdateEdge.to,dis[tmpUpdateEdge.to]));
            }else if(dis[tmpUpdateEdge.to] == dis[tmpEdge.to] + tmpUpdateEdge.weight) {
                if(tmpEdge.to < prev[tmpUpdateEdge.to]) prev[tmpUpdateEdge.to] = tmpEdge.to;
                que.push(Edge(tmpUpdateEdge.to,dis[tmpUpdateEdge.to]));
            }
        }
    }
}
/*
void spfa(Graph &graph,int n,int start,int *dis,int *prev) {
    memset(dis,-INF,sizeof(int) * n);
    bool *vis = new bool[n];
    memset(vis,false,sizeof(bool) * n);
    memset(prev,INF,sizeof(int) * n);
    queue<int> que;
    que.push(start);
    vis[start] = true;
    dis[start] = 0;
    while(!que.empty()) {
        int tmpPoint = que.front();
        que.pop();
        vis[tmpPoint] = false;
        for(int i = graph.heads[tmpPoint];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[tmpPoint] + tmpEdge.weight > dis[tmpEdge.to]) {
                dis[tmpEdge.to] = dis[tmpPoint] + tmpEdge.weight;
                prev[tmpEdge.to] = tmpPoint;
                if(!vis[tmpEdge.to]) {
                    vis[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }else if(dis[tmpPoint] + tmpEdge.weight == dis[tmpEdge.to]) {
                if(tmpPoint < prev[tmpEdge.to]) {
                    prev[tmpEdge.to] = tmpPoint;
                    if(!vis[tmpEdge.to]) {
                        vis[tmpEdge.to] = true;
                        que.push(tmpEdge.to);
                    }
                }
            }
        }
    }
}
*/
int main() {
    int n,m;
    while(~scanf("%d%d",&n,&m)) {
        Graph graph(m,n);
        bool *isStart = new bool[n],*isEnd = new bool[n];
        memset(isStart,true,sizeof(bool) * n);
        memset(isEnd,true,sizeof(bool) * n);
        for(int i = 0;i < m;i++) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            u--;v--;
            isStart[u] = false;
            isEnd[v] = false;
            graph.addEdge(v,u,w);
        }
        int start = - 1,end = -1;
        for(int i = 0;i < n;i++) {
            if(isStart[i]) {
                start = i;
            }
            if(isEnd[i]) {
                end = i;
            }
        }
        int *dis = new int[n];
        int *prev = new int[n];
        dijkstra(graph,n,start,dis,prev);
        printf("%d\n",dis[end]);
        int *result = new int[n],resultIndex = 0;
        int doingIndex = end;
        while(doingIndex != INF) {
            result[resultIndex++] = doingIndex;
            doingIndex = prev[doingIndex];
        }
        for(int i = 0;i < resultIndex - 1;i++) {
            printf("%d %d\n",result[i] + 1,result[i + 1] + 1);
        }
    }
    return 0;
}
