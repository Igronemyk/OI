#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_EDGE_RANGE = 1e5;

template<typename T>
struct Queue {
    T *values;
    int head,tail;

    Queue(int size) {
        values = new T[size];
        head = 0;
        tail = 0;
    }

    void push(T value) {
        values[tail++] = value;
    }

    void pop() {
        head++;
    }

    T front() {
        return values[head];
    }

    bool empty() {
        return head == tail;
    }

};

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads,*countIn;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
        countIn = new int[nodeSize];
        memset(countIn,0,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
        countIn[v]++;
    }

};

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>();
    Graph graph(MAX_EDGE_RANGE,N);
    for(int i = 0;i < N;i++) {
        int tmpValue;
        while((tmpValue = read<int>()) != 0) {
            graph.addEdge(i,tmpValue - 1);
        }
    }
    Queue<int> que(N);
    for(int i = 0;i < N;i++) {
        if(graph.countIn[i] == 0) {
            que.push(i);
        }
    }
    while(!que.empty()) {
        int tmpValue = que.front();
        que.pop();
        printf("%d ",tmpValue + 1);
        for(int i = graph.heads[tmpValue];i != - 1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            graph.countIn[tmpEdge.to]--;
            if(graph.countIn[tmpEdge.to] == 0) {
                que.push(tmpEdge.to);
            }
        }
    }
    printf("\n");
    return 0;
}
