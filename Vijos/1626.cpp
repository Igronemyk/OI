#include <cstdio>
#include <cstring>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    } *egdes;
    int tot,*heads;

    Graph(int edgeCount,int nodeCount) {
        edges = new Edge[edgeCount];
        heads = new int[nodeCount];
        memset(heads,-1,sizeof(int) * headCount);
        tot = 0;
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

    bool isLeafNode(int pos) {
        return heads[pos] == -1;
    }
};

Graph *oldGraph;

int main() {
    int N = read<int>(),M = read<int>();
    oldGraph = new Graph(M,N);
    for(int i = 0;i < M;i++) {
        int A = read<int>(),B = read<int>();
        A--; B--;
    }

    return 0;
}
