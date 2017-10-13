#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}
struct Graph {
    struct Node {
        int to,weight,next;
        Node() : to(-1) , weight(-1) , next(-1) {}
        Node(int to,int weight,int next) : to(to) , weight(weight) ,next(next) {}
    } *edges;
    int tot,*heads;
    Graph(int nodeSize,int edgeSize) {
        tot = 0;
        edges = new Node[edgeSize];
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].to = v;
        edges[tot].weight = w;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};
int * spfaFirst(Graph &graph,int nodeSize,int start,int initValue) {
    int *dis = new int[nodeSize];
    memset(dis,INF,sizeof(int) * nodeSize);
    bool *vis = new bool[nodeSize];
    memset(vis,false,sizeof(bool) * nodeSize);
    vis[start] = true;
    dis[start] = initValue;
    queue<int> que;
    que.push(start);
    while(!que.empty()) {
        int ind = que.front();
        que.pop();
        vis[ind] = false;
        for(int i = graph.heads[ind];i != -1;i = graph.edges[i].next) {
            Graph::Node &tmpEdge = graph.edges[i];
            if(dis[tmpEdge.to] > tmpEdge.weight || dis[tmpEdge.to] > dis[ind]) {
                dis[tmpEdge.to] = min(tmpEdge.weight,dis[ind]);
                if(!vis[tmpEdge.to]) {
                    vis[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
    return dis;
}

int *spfaSecond(Graph &graph,int nodeSize,int start,int initValue) {
    int *dis = new int[nodeSize];
    memset(dis,-INF,sizeof(int) * nodeSize);
    bool *vis = new bool[nodeSize];
    memset(vis,false,sizeof(bool) * nodeSize);
    vis[start] = true;
    dis[start] = initValue;
    queue<int> que;
    que.push(start);
    while(!que.empty()) {
        int ind = que.front();
        que.pop();
        vis[ind] = false;
        for(int i = graph.heads[ind];i != -1;i = graph.edges[i].next) {
            Graph::Node &tmpEdge = graph.edges[i];
            if(dis[tmpEdge.to] < tmpEdge.weight || dis[tmpEdge.to] < dis[ind]) {
                dis[tmpEdge.to] = max(tmpEdge.weight,dis[ind]);
                if(!vis[tmpEdge.to]) {
                    vis[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
    return dis;
}

int main() {
    int n = read<int>(),m = read<int>();
    int *value = new int[n];
    for(int i = 0;i < n;i++) value[i] = read<int>();
    Graph firstGraph(n,m * 2),secondGraph(n,m * 2);
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(), opt = read<int>();
        u--;v--;
        if(opt == 1) {
            firstGraph.addEdge(u,v,value[v]);
            secondGraph.addEdge(v,u,value[u]);
        }else if(opt == 2) {
            firstGraph.addEdge(u,v,value[v]);
            firstGraph.addEdge(v,u,value[u]);
            secondGraph.addEdge(u,v,value[v]);
            secondGraph.addEdge(v,u,value[u]);
        }
    }
    int *dis1 = spfaFirst(firstGraph,n,0,value[0]);
    int *dis2 = spfaSecond(secondGraph,n,n - 1,value[n - 1]);
    int result = 0;
    for(int i = 0;i < n;i++){
        result = max(result,dis2[i] - dis1[i]);
    }
    printf("%d\n",result);
    return 0;
}

