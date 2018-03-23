#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <queue>

using namespace std;

const long long INF = LLONG_MAX;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,from,to;
        long long weight,flow;
    };

    Edge *edges;
    int tot,*heads,nodeSize;

    Graph(int edgeSize,int nodeSize) : nodeSize(nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,long long flow,long long w) {
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

};

void spfa(Graph &graph,int start,bool *inQue,long long *dis) {
    fill(dis,dis + graph.nodeSize,INF);
    memset(inQue,false,sizeof(bool) * graph.nodeSize);
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    inQue[start] = true;
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        inQue[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[now] + tmpEdge.weight < dis[tmpEdge.to]) {
                dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
                if(!inQue[tmpEdge.to]) {
                    inQue[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
}

struct Dinic {
    int *nowEdge,*step,nodeSize,start,target;
    Graph *graph;
    Dinic(int nodeSize,Graph *graph,int start,int target) : nodeSize(nodeSize) , start(start) , target(target) , graph(graph) {
        nowEdge = new int[nodeSize];
        step = new int[nodeSize];
    }

    bool bfs() {
        queue<int> que;
        memset(step,-1,sizeof(int) * nodeSize);
        step[start] = 0;
        que.push(start);
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
                Graph::Edge &tmpEdge = graph->edges[i];
                if(tmpEdge.flow <= 0 || step[tmpEdge.to] != -1) continue;
                step[tmpEdge.to] = step[now] + 1;
                if(tmpEdge.to == target) return true;
                que.push(tmpEdge.to);
            }
        }
        return false;
    }

    long long dfs(int now,long long maxFlow) {
        if(now == target) return maxFlow;
        long long result = 0;
        for(int i = nowEdge[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.flow <= 0 || step[tmpEdge.to] != step[now] + 1) continue;
            long long tmpResult = dfs(tmpEdge.to,min(maxFlow - result,tmpEdge.flow));
            tmpEdge.flow -= tmpResult;
            graph->edges[i ^ 1].flow += tmpResult;
            result += tmpResult;
            if(result == maxFlow) break;
        }
        if(result == 0) {
            step[now] = -1;
        }
        return result;
    }

    long long maxFlow() {
        long long result = 0;
        while(bfs()) {
            memcpy(nowEdge,graph->heads,sizeof(int) * nodeSize);
            result += dfs(start,INF);
        }
        return result;
    }
};



int main() {
    int n = read<int>(),m = read<int>();
    Graph graph(m * 2,n),dinicGraph(n * 2 + m * 4,n * 2);
    bool *inQue = new bool[n];
    long long *dis = new long long[n];
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph.addEdge(u,v,0,w);
        graph.addEdge(v,u,0,w);
    }
    spfa(graph,0,inQue,dis);
    for(int i = 0;i < graph.tot;i++) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dis[tmpEdge.from] + tmpEdge.weight == dis[tmpEdge.to]) {
            dinicGraph.addEdge(tmpEdge.from + n,tmpEdge.to,INF,0);
            dinicGraph.addEdge(tmpEdge.to,tmpEdge.from + n,0,0);
        }
    }
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        if(i == 0 || i == n - 1) {
            dinicGraph.addEdge(i,i + n,INF,0);
        }else {
            dinicGraph.addEdge(i,i + n,tmpValue,0);
        }
        dinicGraph.addEdge(i + n,i,0,0);
    }
    int S = 0,T = n * 2 - 1;
    Dinic dinic(n * 2,&dinicGraph,S,T);
    printf("%lld\n",dinic.maxFlow());
    return 0;
}
