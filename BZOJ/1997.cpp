#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 210;
const int MAXM = MAXN * 3;

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
    Edge edges[MAXM * MAXM * 2];
    int tot,heads[MAXM];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
} graph;

typedef pair<int,int> Edge;

Edge edges[MAXM];
int pos[MAXN],color[MAXM];

bool cross(int x1,int y1,int x2,int y2) {
    x1 = pos[x1]; y1 = pos[y1]; x2 = pos[x2]; y2 = pos[y2];
    if(x1 == x2 || x1 == y2 || y1 == x2 || y1 == y2) return false;
    if(x1 > y1) swap(x1,y1);
    if(x2 > y2) swap(x2,y2);
    if(x1 > x2) {
        swap(x1,x2);
        swap(y1,y2);
    }
    if(x1 < x2 && x2 < y1 && y2 > y1) {
        return true;
    }
    return false;
}

bool dfs(int now) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(color[tmpEdge.to] != -1) {
            if(color[tmpEdge.to] == color[now]) return false;
        }else {
            color[tmpEdge.to] = color[now] ^ 1;
            bool result = dfs(tmpEdge.to);
            if(!result) return false;
        }
    }
    return true;
}

int main() {
    int T = read<int>();
    while(T--) {
        graph.clear();
        int N = read<int>(),M = read<int>();
        if(M > (3 * N - 6)) {
            for(int i = 1;i <= M;i++) {
                read<int>(); read<int>();
            }
            for(int i = 1;i <= N;i++) {
                read<int>();
            }
            printf("NO\n");
            continue;
        }
        for(int i = 1;i <= M;i++) {
            int u = read<int>(),v = read<int>();
            edges[i] = make_pair(u,v);
        }
        for(int i = 1;i <= N;i++) {
            pos[read<int>()] = i;
        }
        for(int i = 1;i <= M;i++) {
            for(int j = 1;j < i;j++) {
                int x1 = edges[i].first,y1 = edges[i].second,x2 = edges[j].first,y2 = edges[j].second;
                if(!cross(x1,y1,x2,y2)) continue;
                graph.addEdge(i,j);
                graph.addEdge(j,i);
            }
        }
        memset(color,-1,sizeof(color));
        bool solved = true;
        for(int i = 1;i <= M;i++) {
            if(color[i] == -1) {
                color[i] = 0;
                if(!dfs(i)) {
                    solved = false;
                    break;
                }
            }
        }
        printf(solved ? "YES\n" : "NO\n");
    }
    return 0;
}
