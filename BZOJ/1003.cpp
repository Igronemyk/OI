#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cstddef>

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
    };
    Edge *edges;
    int tot,*heads,nodeSize;

    Graph(int edgeSize,int nodeSize) : nodeSize(nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
};

void spfa(int start,bool *visit,bool *banned,Graph &graph,int *dis){
    int n = graph.nodeSize;
    memset(dis,INF,sizeof(int) * n);
    if(banned[start]) return;
    memset(visit,false,sizeof(bool) * n);
    dis[start] = 0;
    queue<int> que;
    visit[start] = true;
    que.push(start);
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(banned[tmpEdge.to]) continue;
            if(dis[tmpEdge.to] > dis[now] + tmpEdge.weight) {
                dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
                if(!visit[tmpEdge.to]) {
                    visit[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
}

struct Info {
    int sign,left,right;
    Info() : sign(-1) , left(-1) , right(-1) { }
    Info(int sign,int left,int right) : sign(sign) , left(left) , right(right) { }

    bool isContains(int otherLeft,int otherRight) {
        return max(left,otherLeft) <= min(right,otherRight);
    }
};

void getCost(int infoSize,int n,Info *infos,Graph &graph,int **costs) {
    bool *banned = new bool[graph.nodeSize];
    bool *visit = new bool[graph.nodeSize];
    int *dis = new int[graph.nodeSize];
    for(int i = 1;i <= n;i++) {
        for(int j = i;j <= n;j++) {
            memset(banned,false,sizeof(bool) * graph.nodeSize);
            for(int l = 0;l < infoSize;l++) {
                if(infos[l].isContains(i,j)) {
                    banned[infos[l].sign] = true;
                }
            }
            spfa(0,visit,banned,graph,dis);
            if(dis[graph.nodeSize - 1] == INF) {
                costs[i][j] = INF;
            }else {
                costs[i][j] = dis[graph.nodeSize - 1] * (j - i + 1);
            }
        }
    }
}

int main() {
    int n = read<int>(),m = read<int>(),K = read<int>(),e = read<int>();
    Graph graph(e * 2,m);
    for(int i = 0;i < e;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    int d = read<int>();
    Info *infos = new Info[d];
    for(int i = 0;i < d;i++) {
        int sign = read<int>(),left = read<int>(),right = read<int>();
        sign--;
        infos[i] = Info(sign,left,right);
    }
    int **costs = new int*[n + 1];
    for(int i = 0;i <= n;i++) {
        costs[i] = new int[n + 1];
    }
    getCost(d,n,infos,graph,costs);
    int *dp = new int[n + 1];
    memset(dp,INF,sizeof(int) * (n + 1));
    dp[0] = 0;
    for(int i = 1;i <= n;i++) {
        dp[i] = costs[1][i];
        for(int j = i - 1;j >= 1;j--) {
            dp[i] = min(dp[i],dp[j] + costs[j + 1][i] + K);
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}
