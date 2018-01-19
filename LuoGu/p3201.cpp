#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e6 + 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 +c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads,*start;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
        start = new int[nodeSize];
        memset(start,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        if(heads[u] == -1) {
            start[u] = tot;
        }
        heads[u] = tot++;
    }

    void merge(int u,int v) {
        if(start[v] == -1) return;
        edges[start[v]].next = heads[u];
        for(int i = start[v];i != -1;i = edges[i].next) {
            start[v] = i;
        }
        heads[u] = -1;
        start[u] = -1;
    }
    ~Graph() {
        delete[] edges;
        delete[] heads;
        delete[] start;
    }

};

int main() {
    int N = read<int>(),M = read<int>(),*colors = new int[MAX_VAL_RANGE],*nowColor = new int[N],*colorCnt = new int[MAX_VAL_RANGE];
    memset(colorCnt,0,sizeof(int) * MAX_VAL_RANGE);
    for(int i = 0;i < MAX_VAL_RANGE;i++) colors[i] = i;
    Graph graph(N * 30,MAX_VAL_RANGE);
    int result = 1;
    for(int i = 0;i < N;i++) {
        int tmpColor = read<int>();
        nowColor[i] = tmpColor;
        if(i > 0 && nowColor[i] != nowColor[i - 1]) result++;
        colorCnt[tmpColor]++;
        graph.addEdge(tmpColor,i);
    }
    while(M--) {
        int opt = read<int>();
        if(opt == 1) {
            int x = read<int>(),y = read<int>();
            if(x == y) continue;
            if(colorCnt[colors[x]] > colorCnt[colors[y]]) swap(colors[x],colors[y]);
            x = colors[x];
            y = colors[y];
            colorCnt[y] += colorCnt[x];
            colorCnt[x] = 0;
            for(int i = graph.heads[x];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.to != 0) {
                    if(nowColor[tmpEdge.to - 1] == y) {
                        result--;
                    }
                }
                if(tmpEdge.to != N - 1) {
                    if(nowColor[tmpEdge.to + 1] == y) {
                        result--;
                    }
                }
            }
            for(int i = graph.heads[x];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                nowColor[tmpEdge.to] = y;
            }
            graph.merge(x,y);
        }else {
            printf("%d\n",result);
        }
    }
    delete[] colors;
    delete[] nowColor;
    delete[] colorCnt;
    return 0;
}
