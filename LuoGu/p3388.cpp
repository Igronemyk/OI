#include <cstdio>
#include <algorithm>
#include <cstring>

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
    } *edges;
    int tot,*heads;
    Graph(int edgeSize,int nodeSize) {
       edges = new Edge[edgeSize];
       heads = new int[nodeSize];
       memset(heads,-1,sizeof(int) * nodeSize);
       tot = 0;
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

void Tarjan(int now,int father,int &nowTime,int &cutPoint,int *dfn,int *low,Graph &graph,bool *inStack,bool *isCutPoint) {
    dfn[now] = nowTime;
    low[now] = nowTime++;
    inStack[now] = true;
    int childCount = 0;
    bool skipped = false;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father && !skipped) {
            skipped = true;
            continue;
        }
        if(dfn[tmpEdge.to] == -1) {
            Tarjan(tmpEdge.to,now,nowTime,cutPoint,dfn,low,graph,inStack,isCutPoint);
            low[now] = min(low[now],low[tmpEdge.to]);
            childCount++;
            if(father != -1 && low[tmpEdge.to] >= dfn[now] && !isCutPoint[now]) {
                isCutPoint[now] = true;
                cutPoint++;
            }

        }else if(inStack[tmpEdge.to]) {
            low[now] = min(low[now],dfn[tmpEdge.to]);
        }
    }
    if(father == -1 && childCount > 1 && !isCutPoint[now]) {
        isCutPoint[now] = true;
        cutPoint++;
    }
}

int main() {
    int n = read<int>(),m = read<int>();
    Graph graph(m * 2,n);
    for(int i = 0;i < m;i++) {
        int x = read<int>(),y = read<int>();
        x--; y--;
        graph.addEdge(x,y);
        graph.addEdge(y,x);
    }
    int *dfn = new int[n],*low = new int[n],nowTime = 0,cutPoint = 0;
    bool *inStack = new bool[n],*isCutPoint = new bool[n];
    memset(dfn,-1,sizeof(int) * n);
    memset(low,-1,sizeof(int) * n);
    memset(inStack,false,sizeof(bool) * n);
    memset(isCutPoint,false,sizeof(bool) * n);
    for(int i = 0;i < n;i++) {
        if(dfn[i] == -1) {
            Tarjan(i,-1,nowTime,cutPoint,dfn,low,graph,inStack,isCutPoint);
        }
    }
    printf("%d\n",cutPoint);
    for(int i = 0;i < n;i++) {
        if(isCutPoint[i]) {
            printf("%d ",i + 1);
        }
    }
    printf("\n");
    return 0;
}
