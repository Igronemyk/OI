#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 0x3f3f3f3f;

struct Graph{
    struct Node{
        int to,weight,next;
    } nodes[500010];
    int edges,head[10010];
    void init(){
        edges = 0;
        memset(head,-1,sizeof(head));
    }

    void addEdge(int from,int to,int weight){
        nodes[edges].to = to;
        nodes[edges].weight = weight;
        nodes[edges].next = head[from];
        head[from] = edges++;
    }
};

struct Edge{
    int to,weight;
    Edge() : to(-1) , weight(-1) {}
    Edge(int to,int weight) : to(to) , weight(weight) {}
};

struct Comparator{
    bool operator () (Edge e1,Edge e2){
        return e1.weight > e2.weight;
    }
};
int N,M,S,vis[10010],dis[10010];
Graph graph;


void dijkstra(){
    memset(vis,false,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    dis[S] = 0;
    priority_queue<Edge,vector<Edge>,Comparator> pq;
    pq.push(Edge(S,0));
    for(int round = 1;round <= N;round++){
        while(!pq.empty() && vis[pq.top().to]){
            pq.pop();
        }
        if(pq.empty()) break;
        Edge tmpEdge = pq.top();
        pq.pop();
        vis[tmpEdge.to] = true;
        for(int i = graph.head[tmpEdge.to];i != -1;i = graph.nodes[i].next){
            if(dis[graph.nodes[i].to] > dis[tmpEdge.to] + graph.nodes[i].weight){
                dis[graph.nodes[i].to] = dis[tmpEdge.to] + graph.nodes[i].weight;
                pq.push(Edge(graph.nodes[i].to,dis[graph.nodes[i].to]));
            }
        }
    }
}

int main(){
    N = read<int>();M = read<int>();S = read<int>();
    graph.init();
    for(int i = 0;i < M;i++){
        int F = read<int>(),G = read<int>(),W = read<int>();
        graph.addEdge(F,G,W);
    }
    dijkstra();
    for(int i = 1;i <= N;i++){
        printf("%d ",dis[i] == INF ? 2147483647 : dis[i]);
    }
    printf("\n");
    return 0;
}
