#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

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
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

};

int N,S;

void dfs(int now,int father,int nowDepth,Graph &graph,int *values,int *nowValues,int &result) {
    nowValues[nowDepth] = nowValues[nowDepth - 1] + values[now];
    int *pos = lower_bound(nowValues,nowValues + nowDepth + 1,nowValues[nowDepth] - S);
    if(pos != nowValues + nowDepth + 1 && *(pos) == nowValues[nowDepth] - S) {
        result++;
    }
    for(int i = graph.heads[now];i != - 1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now,nowDepth + 1,graph,values,nowValues,result);
    }
}

int main() {
    N = read<int>(); S = read<int>();
    int *values = new int[N],*nowValues = new int[N + 1];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int x = read<int>(),y = read<int>();
        x--; y--;
        graph.addEdge(x,y);
        graph.addEdge(y,x);
    }
    int result = 0;
    nowValues[0] = 0;
    dfs(0,-1,1,graph,values,nowValues,result);
    printf("%d\n",result);
    return 0;
}
