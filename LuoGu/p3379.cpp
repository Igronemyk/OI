/*
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
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int fatherU = getFather(u),fatherV = getFather(v);
        father[fatherV] = fatherU;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
};


struct Graph {
    struct Edge {
        int next,to,sign;
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

    void addEdge(int u,int v,int sign) {
        edges[tot].to = v;
        edges[tot].sign = sign;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

void Tarjan(int now,int father,Graph &graph,Graph &querys,BCS &bcset,int *result,bool *visit) {
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        Tarjan(tmpEdge.to,now,graph,querys,bcset,result,visit);
        bcset.merge(now,tmpEdge.to);
    }
    for(int i = querys.heads[now];i != -1;i = querys.edges[i].next) {
        Graph::Edge &tmpEdge = querys.edges[i];
        if(result[tmpEdge.sign] != -1) continue;
        if(!visit[tmpEdge.to]) continue;
        result[tmpEdge.sign] = bcset.getFather(tmpEdge.to);
    }
}

int main() {
    int N = read<int>(),M = read<int>(),S = read<int>();
    S--;
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int x = read<int>(),y = read<int>();
        x--; y--;
        graph.addEdge(x,y);
        graph.addEdge(y,x);
    }
    Graph querys(M * 2,N);
    for(int i = 0;i < M;i++) {
        int a = read<int>(),b = read<int>();
        a--; b--;
        querys.addEdge(a,b,i);
        querys.addEdge(b,a,i);
    }
    int *result = new int[N];
    memset(result,-1,sizeof(int) * N);
    bool *visit = new bool[N];
    memset(visit,false,sizeof(bool) * N);
    BCS bcset(N);
    Tarjan(S,-1,graph,querys,bcset,result,visit);
    for(int i = 0;i < N;i++) {
        printf("%d\n",result[i] + 1);
    }
    return 0;
}
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_DEPTH = 20;

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

void dfs(int now,int nowDepth,int nowFather,Graph &graph,int *depth,int **father) {
    depth[now] = nowDepth;
    father[now][0] = nowFather;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == nowFather) continue;
        dfs(tmpEdge.to,nowDepth + 1,now,graph,depth,father);
    }
}

int getLCA(int a,int b,int *depth,int **father) {
    if(depth[a] > depth[b]) {
        swap(a,b);
    }
    for(int i = MAX_DEPTH - 1;i >= 0;i--) {
        if((~father[b][i]) && depth[father[b][i]] >= depth[a]) {
            b = father[b][i];
        }
    }
    if(a == b) {
        return a;
    }
    for(int i = MAX_DEPTH - 1;i >= 0;i--) {
        if((~father[a][i]) && (~father[b][i]) && father[a][i] != father[b][i]) {
            a = father[a][i];
            b = father[b][i];
        }
    }
    return father[a][0];
}

int main() {
    int N = read<int>(),M = read<int>(),S = read<int>();
    S--;
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int x = read<int>(), y = read<int>();
        x--; y--;
        graph.addEdge(x,y);
        graph.addEdge(y,x);
    }
    int *depth = new int[N],**father = new int*[N];
    memset(depth,-1,sizeof(int) * N);
    for(int i = 0;i < N;i++) {
        father[i] = new int[MAX_DEPTH];
        memset(father[i],-1,sizeof(int) * MAX_DEPTH);
    }
    dfs(S,0,-1,graph,depth,father);
    for(int j = 1;j < MAX_DEPTH;j++) {
        for(int i = 0;i < N;i++) {
            if(~father[i][j - 1]) {
                father[i][j] = father[father[i][j - 1]][j - 1];
            }
        }
    }
    for(int i = 0;i < M;i++) {
        int a = read<int>(),b = read<int>();
        a--; b--;
        printf("%d\n",getLCA(a,b,depth,father) + 1);
    }
    return 0;
}
