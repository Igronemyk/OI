#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const long long INF = 1e18;

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
    Edge *edges;
    int tot,*heads;

    Graph() : edges(NULL) , tot(-1) , heads(NULL) { }

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
        tot = 0;
    }

    void addEdge(int u,int v,int flow) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

};

template<typename T>
struct Queue {
    T *values;
    int head,tail,maxSize,nowSize;

    Queue() : values(NULL) , head(-1) , tail(-1) , maxSize(-1), nowSize(-1) { }

    Queue(int maxSize) : maxSize(maxSize) , head(0) , tail(0), nowSize(0) {
        values = new T[maxSize];
    }

    void push_front(T value) {
        nowSize++;
        head = getPreIndex(head);
        values[head] = value;
    }

    void pop_front() {
        nowSize--;
        head = getNextIndex(head);
    }

    void push_back(T value) {
        nowSize++;
        values[tail] = value;
        tail = getNextIndex(tail);
    }

    void pop_back() {
        nowSize--;
        tail = getPreIndex(tail);
    }

    T front() {
        return values[head];
    }

    T back() {
        return values[getPreIndex(tail)];
    }

    bool isEmpty() {
        return nowSize == 0;
    }

    int size() {
        return nowSize;
    }

    void clear() {
        head = 0;
        tail = 0;
        nowSize = 0;
    }

    int getPreIndex(int index) {
        int tmpValue = index - 1;
        if(tmpValue < 0) tmpValue += maxSize;
        return tmpValue;
    }

    int getNextIndex(int index) {
        int tmpValue = index + 1;
        if(tmpValue >= maxSize) tmpValue -= maxSize;
        return tmpValue;
    }
};

class Solver {
private:
    Graph graph;
    Queue<int> bfsQue;
    int *nowEdge,*step,N,M,S,T;

    bool bfs() {
        bfsQue.clear();
        bfsQue.push_back(S);
        memset(step,-1,sizeof(int) * N);
        step[S] = 0;
        while(!bfsQue.isEmpty()) {
            int now = bfsQue.front();
            bfsQue.pop_front();
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.flow <= 0 || step[tmpEdge.to] != -1) continue;
                step[tmpEdge.to] = step[now] + 1;
                bfsQue.push_back(tmpEdge.to);
                if(tmpEdge.to == T) return true;
            }
        }
        return false;
    }

    long long dfs(int now,long long nowMaxFlow) {
        if(now == T) return nowMaxFlow;
        long long result = 0;
        for(int i = nowEdge[now];result < nowMaxFlow && i != -1;i = graph.edges[i].next) {
            nowEdge[now] = i;
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.flow <= 0 || step[tmpEdge.to] != step[now] + 1) continue;
            long long tmpFlow = dfs(tmpEdge.to,min(nowMaxFlow - result,(long long)tmpEdge.flow));
            result += tmpFlow;
            tmpEdge.flow -= tmpFlow;
            //graph.edges[i ^ 1].flow += tmpFlow;
            //if(result == nowMaxFlow) break;//当前弧优化，如果i为引用，break一定要写在这里，写在循环判断内会导致i发生变化
        }
        if(result == 0) {
            step[now] = -1;
        }
        return result;
    }

    long long dinic() {
        long long result = 0;
        while(bfs()) {
            for(int i = 0;i < N;i++) {
                nowEdge[i] = graph.heads[i];
            }
            result += dfs(S,INF);
        }
        return result;
    }

public:
    void solve() {
        N = read<int>(); M = read<int>(); S = read<int>() - 1; T = read<int>() - 1;
        graph = Graph(M,N);
        bfsQue = Queue<int>(N);
        nowEdge = new int[N];
        step = new int[N];
        for(int i = 0;i < M;i++) {
            int u = read<int>() - 1,v = read<int>() - 1,w = read<int>();
            graph.addEdge(u,v,w);
            //graph.addEdge(v,u,0);
        }
        printf("%lld\n",dinic());
    }

};

int main() {
    Solver solver;
    solver.solve();
    return 0;
}
