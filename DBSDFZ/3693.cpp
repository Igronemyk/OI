#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstddef>
#include <cstring>
#include <iostream>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
struct Queue {
    T *values;
    int head,tail,maxSize,nowSize;

    Queue() : values(NULL) , head(-1) , tail(-1) { }
    Queue(int maxSize) : head(0) , tail(0) , maxSize(maxSize) , nowSize(0) {
        values = new T[maxSize];
    }

    void push(T val) {
        values[tail] = val;
        tail = getNextPos(tail);
        nowSize++;
    }

    void pop() {
        head = getNextPos(head);
        nowSize--;
    }

    int getPrePos(int pos) {
        pos--;
        if(pos < 0) pos += nowSize;
        return pos;
    }

    int getNextPos(int pos) {
        pos++;
        if(pos >= maxSize) pos -= maxSize;
        return pos;
    }

    int size() {
        return nowSize;
    }

    bool empty() {
        return size() == 0;
    }

    void clear() {
        head = 0;
        tail = 0;
        nowSize = 0;
    }

    T front() {
        return values[head];
    }

};

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,from,to,weight,flow;
    };

    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int flow,int w) {
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

    ~Graph() {
        delete[] edges;
        delete[] heads;
    }

};

struct EK {

    int size,start,target,*dis,*prevEdge;
    Graph *graph;
    Queue<int> que;
    bool *isInQueue;

    EK() : size(-1) , start(-1) , target(-1) , dis(NULL) , prevEdge(NULL) , graph(NULL) , isInQueue(NULL) { }
    EK(int size,int start,int target,Graph *graph) : size(size) , start(start) , target(target) , graph(graph) {
        dis = new int[size];
        prevEdge = new int[size];
        isInQueue = new bool[size];
        que = Queue<int>(size);
    }

    pair<int,int> augment() {
        fill(dis,dis + size,INF);
        memset(prevEdge,-1,sizeof(int) * size);
        memset(isInQueue,false,sizeof(bool) * size);
        que.clear();
        que.push(start);
        isInQueue[start] = true;
        dis[start] = 0;
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            isInQueue[now] = false;
            for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
                Graph::Edge &tmpEdge = graph->edges[i];
                if(tmpEdge.flow <= 0 || dis[now] * 1LL + tmpEdge.weight >= dis[tmpEdge.to]) continue;
                dis[tmpEdge.to] = dis[now] * 1LL + tmpEdge.weight;
                prevEdge[tmpEdge.to] = i;
                if(!isInQueue[tmpEdge.to]) {
                    que.push(tmpEdge.to);
                    isInQueue[tmpEdge.to] = true;
                }
            }
        }
        if(dis[target] == INF) {
            return make_pair(0,0);
        }
        int maxFlow = INF;
        for(int i = target;prevEdge[i] != -1;i = graph->edges[prevEdge[i]].from) {
            Graph::Edge &tmpEdge =  graph->edges[prevEdge[i]];
            maxFlow = min(maxFlow,tmpEdge.flow);
        }
        for(int i = target;prevEdge[i] != -1;i = graph->edges[prevEdge[i]].from) {
            Graph::Edge &tmpEdge = graph->edges[prevEdge[i]];
            tmpEdge.flow -= maxFlow;
            graph->edges[prevEdge[i] ^ 1].flow += maxFlow;
        }
        return make_pair(maxFlow,dis[target]);
    }

    pair<int,int> maxFlowMinCost() {
        int maxFlow = 0,minCost = 0;
        while(true) {
            pair<int,int> value = augment();
            if(value.first == 0) {
                break;
            }
            maxFlow += value.first;
            minCost += value.first * value.second;
        }
        return make_pair(maxFlow,minCost);
    }

    ~EK() {
        delete[] dis;
        delete[] prevEdge;
        delete[] isInQueue;
    }

};

int main() {
    int N = read<int>(),M = read<int>();
    Graph graph(M * 4 + 4,N + 2);
    int S = 0,T = N + 1;
    graph.addEdge(S,1,2,0);
    graph.addEdge(1,S,0,0);
    graph.addEdge(N,T,2,0);
    graph.addEdge(T,N,0,0);
    for(int i = 0;i < M;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,1,w);
        graph.addEdge(v,u,0,-w);
        graph.addEdge(v,u,1,w);
        graph.addEdge(u,v,0,-w);
    }
    EK ek(N + 2,S,T,&graph);
    pair<int,int> result = ek.maxFlowMinCost();
    printf("%d\n",result.second);
    return 0;
}
