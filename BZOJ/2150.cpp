#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 10010;
const int MAXN = 2510;
const int MAX_RANGE = 51;

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
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

char graph1[MAX_RANGE][MAX_RANGE];
int mapedIndex[MAX_RANGE][MAX_RANGE],nowIndex,nowTime;

int M,N,R,C;

void addEdge(int x,int y,int distX,int distY) {
    if(distX <= 0 || distX > M || distY <= 0 || distY > N || graph1[distX][distY] != '.') return;
    graph.addEdge(mapedIndex[x][y],mapedIndex[distX][distY]);
}

int visit[MAXN],match[MAXN];

bool augment(int now) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] == nowTime) continue;
        visit[tmpEdge.to] = nowTime;
        if(match[tmpEdge.to] == -1 || augment(match[tmpEdge.to])) {
            match[tmpEdge.to] = now;
            return true;
        }
    }
    return false;
}

int hungry() {
    memset(match,-1,sizeof(match));
    int cnt = 0;
    for(int i = 1;i <= M;i++) {
        for(int j = 1;j <= N;j++) {
            if(graph1[i][j] != '.') continue;
            nowTime++;
            if(augment(mapedIndex[i][j])) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    M = read<int>(); N = read<int>(); R = read<int>(); C = read<int>();
    for(int i = 1;i <= M;i++) {
        scanf("%s",graph1[i] + 1);
        for(int j = 1;j <= N;j++) {
            if(graph1[i][j] == '.') {
                mapedIndex[i][j] = nowIndex++;
            }
        }
    }
    for(int i = 1;i <= M;i++) {
        for(int j = 1;j <= N;j++) {
            if(graph1[i][j] == '.') {
                addEdge(i,j,i + R,j - C);
                addEdge(i,j,i + R,j + C);
                addEdge(i,j,i + C,j - R);
                addEdge(i,j,i + C,j + R);
            }
        }
    }
    printf("%d\n",nowIndex - hungry());
    return 0;
}
