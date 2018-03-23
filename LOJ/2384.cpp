#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5;
const int MAXM = 2e6;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,flow;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int flow) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v,int flow) {
        addEdge(u,v,flow);
        addEdge(v,u,0);
    }
} graph;

struct Queue {
    int values[MAXN];
    int head,tail;

    Queue() : head(0) , tail(0) { }

    void push(int value) {
        values[tail++] = value;
    }

    void pop() {
        head++;
    }

    int front() {
        return values[head];
    }

    bool empty() {
        return head == tail;
    }

    void clear() {
        head = 0;
        tail = 0;
    }
} que;

int start,target;

namespace Dinic {

    int step[MAXN],nowEdge[MAXN];

    bool bfs() {
        memset(step,-1,sizeof(step));
        step[start] = 0;
        que.clear();
        que.push(start);
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.flow <= 0 || step[tmpEdge.to] != -1) continue;
                step[tmpEdge.to] = step[now] + 1;
                if(tmpEdge.to == target) return true;
                que.push(tmpEdge.to);
            }
        }
        return false;
    }

    int dfs(int now,int flow) {
        if(now == target) return flow;
        int result = 0;
        for(int &i = nowEdge[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.flow <= 0 || step[tmpEdge.to] != step[now] + 1) continue;
            int tmpResult = dfs(tmpEdge.to,min(flow - result,tmpEdge.flow));
            tmpEdge.flow -= tmpResult;
            graph.edges[i ^ 1].flow += tmpResult;
            result += tmpResult;
            if(result == flow) break;
        }
        if(result == 0) {
            step[now] = -1;
        }
        return result;
    }

    int maxFlow() {
        int result = 0;
        while(bfs()) {
            memcpy(nowEdge,graph.heads,sizeof(graph.heads));
            result += dfs(start,INF);
        }
        return result;
    }

}

int P,Q,R;

int getId(int i,int j,int k) {
    if(i == R) {
        return target;
    }
    return i * R +
}

int main() {
    P = read<int>();Q = read<int>();R = read<int>();

    return 0;
}
