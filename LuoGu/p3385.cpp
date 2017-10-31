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

const int MAXN = 200010;
const int MAXM = 400010;
const int INF = 0x3f3f3f3f;

namespace Adj {
    struct Edge {
        int next,to,weight;
    } edges[MAXM];
    int tot,heads[MAXN];

    void init() {
        memset(heads,-1,sizeof(heads));
        tot = 0;
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
};

using namespace Adj;

bool visit[MAXN],result = false,hasVisited[MAXN];
int dis[MAXN];

void spfa(int now) {

}

int main() {
    int T = read<int>();
    while(T--) {
        init();
        memset(visit,false,sizeof(visit));
        memset(hasVisited,false,sizeof(hasVisited));
        memset(dis,INF,sizeof(dis));
        int N = read<int>(),M = read<int>();
        for(int i = 0;i < M;i++) {
            int a = read<int>(),b = read<int>(),w = read<int>();
            graph.addEdge(a,b,w);
            if(w >= 0) graph.addEdge(b,a,w);
        }
    }
    return 0;
}
