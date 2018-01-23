#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= 1;c = getchar();}
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
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

void dfs(int now,int father,Graph &graph,bool *visit,bool *colors,bool &flag,int &countWhite,int &countBlack) {
    visit[now] = true;
    if(!colors[now]) {
        countWhite++;
    }else {
        countBlack++;
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        if(visit[tmpEdge.to]) {
            if(colors[tmpEdge.to] == colors[now]) {
                flag = false;
                break;
            }else {
                continue;
            }
        }
        colors[tmpEdge.to] = !colors[now];
        dfs(tmpEdge.to,now,graph,visit,colors,flag,countWhite,countBlack);
        if(!flag) break;
    }
}

int main() {
    int N = read<int>(),M = read<int>();
    Graph graph(M * 2,N);
    for(int i = 0;i < M;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    bool *visit = new bool[N],*colors = new bool[N];
    memset(visit,false,sizeof(bool) * N);
    memset(colors,false,sizeof(bool) * N);
    int result = 0;
    for(int i = 0;i < N;i++) {
        bool flag = true;
        int countWhite = 0,countBlack = 0;
        if(!visit[i]) {
            dfs(i,-1,graph,visit,colors,flag,countWhite,countBlack);
            if(!flag) {
                result = -1;
                break;
            }
            result += min(countWhite,countBlack);
        }
    }
    if(result == -1) {
        printf("Impossible\n");
    }else {
        printf("%d\n",result);
    }
    return 0;
}
