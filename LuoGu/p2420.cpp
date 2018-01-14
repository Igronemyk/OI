#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BCS {
    int *father;
    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) {
            father[i] = i;
        }
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int fatherU = getFather(u),fatherV = getFather(v);
        if(fatherU == fatherV) return;
        father[fatherU] = fatherV;
    }
};

struct Graph {

    struct Edge {
        int next,to,weight;
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }

};

struct Info {
    int u,v;
};

void tarjan(int now,int father,bool *visit,Graph &graph,Graph &querys,BCS &bcset,int *xorValue,int *result) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        xorValue[tmpEdge.to] = xorValue[now] ^ tmpEdge.weight;
        tarjan(tmpEdge.to,now,visit,graph,querys,bcset,xorValue,result);
        bcset.merge(tmpEdge.to,now);
    }
    visit[now] = true;
    for(int i = querys.heads[now];i != -1;i = querys.edges[i].next) {
        Graph::Edge &tmpQuery = querys.edges[i];
        if(!visit[tmpQuery.to]) continue;
        result[tmpQuery.weight] = bcset.getFather(tmpQuery.to);
    }
}

int main() {
    int N = read<int>();
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    int M = read<int>();
    Info *infos = new Info[M];
    Graph querys(M * 2,N);
    for(int i = 0;i < M;i++) {
        int u = read<int>(), v = read<int>();
        u--; v--;
        Info &tmpInfo = infos[i];
        infos[i].u = u;
        infos[i].v = v;
        querys.addEdge(u,v,i);
        querys.addEdge(v,u,i);
    }
    bool *visit = new bool[N];
    int *xorValue = new int[N],*result = new int[N];
    BCS bcset(N);
    memset(visit,false,sizeof(bool) * N);
    xorValue[0] = 0;
    tarjan(0,-1,visit,graph,querys,bcset,xorValue,result);
    for(int i = 0;i < M;i++) {
        Info &tmpInfo = infos[i];
        printf("%d\n",xorValue[tmpInfo.u] ^ xorValue[tmpInfo.v]);
    }
    return 0;
}
