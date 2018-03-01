#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,flow;
    };
    Edge *edges;
    int tot,*heads;

    Graph() : edges(NULL) , tot(-1) , heads(NULL) { }

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int flow) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

};

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

    int dfs(int now,int maxFlow) {
        if(now == target) return maxFlow;
        int result = 0;
        for(int i = nowEdge[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.flow <= 0 || step[tmpEdge.to] != step[now] + 1) continue;
            int tmpResult = dfs(tmpEdge.to,min(maxFlow - result,tmpEdge.flow));
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

    int maxFlow() {
        int result = 0;
        while(bfs()) {
            memcpy(nowEdge,graph->heads,sizeof(int) * nodeSize);
            result += dfs(start,INF);
        }
        return result;
    }
};
int N,M;

int getPoint(int x,int y) {
    return x * M + y;
}

int main() {
    N = read<int>();
    M = read<int>();
    Graph graph(2 * (N * (M - 1) + (N - 1) * M + (N - 1) * (M - 1)),N * M);
    for(int i = 0;i < N;i++) {
        for(int j = 0;j < M - 1;j++) {
            int tmpValue = read<int>();
            int u = getPoint(i,j),v = getPoint(i,j + 1);
            graph.addEdge(u,v,tmpValue);
            graph.addEdge(v,u,tmpValue);
        }
    }
    for(int i = 0;i < N - 1;i++) {
        for(int j = 0;j < M;j++) {
            int tmpValue = read<int>();
            int u = getPoint(i,j),v = getPoint(i + 1,j);
            graph.addEdge(u,v,tmpValue);
            graph.addEdge(v,u,tmpValue);
        }
    }
    for(int i = 0;i < N - 1;i++) {
        for(int j = 0;j < M - 1;j++) {
            int tmpValue = read<int>();
            int u = getPoint(i,j),v = getPoint(i + 1,j + 1);
            graph.addEdge(u,v,tmpValue);
            graph.addEdge(v,u,tmpValue);
        }
    }
    Dinic dinic(N * M,&graph,0,N * M - 1);
    printf("%d\n",dinic.maxFlow());
    return 0;
}
