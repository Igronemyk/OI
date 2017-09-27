#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 1000000001;

struct Adj{
    struct Node{
        int to;
        int value;
        int next;
    } nodes[100010];
    int countEdges,heads[10010];
    void init(){
        countEdges = 0;
        memset(heads,-1,sizeof(heads));
    }
    void addEdges(int from,int to,int value){
        nodes[countEdges].to = to;
        nodes[countEdges].value = value;
        nodes[countEdges].next = heads[from];
        heads[from] = countEdges++;
    }
};

Adj graph;

struct Edge{
    int to;
    int cost;
    Edge() : to(-1),cost(-1) {}
    Edge(int to,int cost) : to(to),cost(cost){}
};

struct Comparator{
    bool operator() (Edge e1,Edge e2){
        return e1.cost > e2.cost;
    }
};

int n,m,u,v,s;
int costs[10010],costLimit,midCosts[10010];
long long dis[10010];
bool vis[10010];

void dij(){
    memset(dis,INF,sizeof(dis));
    memset(vis,false,sizeof(vis));
    dis[u] = 0;
    priority_queue<Edge,vector<Edge>,Comparator> pq;
    pq.push(Edge(u,0));
    for(int i = 1;i <= n;i++){
        while(!pq.empty() && vis[pq.top().to]){
            pq.pop();
        }
        if(pq.empty()) break;
        Edge tmpEdge = pq.top();
        pq.pop();
        vis[tmpEdge.to] = true;
        for(int j = graph.heads[tmpEdge.to];j != -1;j = graph.nodes[j].next){
            if(costs[graph.nodes[j].to] > costLimit) continue;
            if(dis[tmpEdge.to] + graph.nodes[j].value < dis[graph.nodes[j].to]) dis[graph.nodes[j].to] = dis[tmpEdge.to] + graph.nodes[j].value;
            pq.push(Edge(graph.nodes[j].to,dis[graph.nodes[j].to]));
        }
    }
}

int main(){
    n = read<int>();m = read<int>();u = read<int>();v = read<int>();s = read<int>();
    for(int i = 1;i <= n;i++){
        costs[i] = read<int>();
        midCosts[i] = costs[i];
    }
    sort(midCosts + 1,midCosts + n + 1);
    graph.init();
    for(int i = 1;i <= m;i++){
        int a = read<int>(),b = read<int>(),c = read<int>();
        graph.addEdges(a,b,c);
        graph.addEdges(b,a,c);
    }
    int left = 1,right = n;
    int ans = INF;
    while(left <= right){
        int mid = (left + right) >> 1;
        costLimit = midCosts[mid];
        dij();
        if(dis[v] <= s){
            right = mid - 1;
            ans = min(ans,midCosts[mid]);
        }else{
            left = mid + 1;
        }
    }
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}
