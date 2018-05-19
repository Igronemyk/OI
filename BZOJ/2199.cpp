#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXM = 8010;
const int MAXN = 2010;

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

bool visit[MAXN];

int N,M,result[MAXN];

void dfs(int now) {
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(!visit[tmpEdge.to]) dfs(tmpEdge.to);
    }
}

bool check(int sign) {
    memset(visit,0,sizeof(visit));
    dfs(sign);
    for(int i = 1;i <= N;i++) {
        if(visit[2 * i] && visit[2 * i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    N = read<int>(); M = read<int>();
    char *buffer = new char[2];
    while(M--) {
        int B = read<int>(); B *= 2;
        {
            scanf("%s",buffer);
            if(buffer[0] == 'Y') {
                B++;
            }
        }
        int C = read<int>(); C *= 2;
        {
            scanf("%s",buffer);
            if(buffer[0] == 'Y') {
                C++;
            }
        }
        graph.addEdge(B ^ 1,C);
        graph.addEdge(C ^ 1,B);
    }
    for(int i = 1;i <= N;i++) {
        bool r1 = check(2 * i),r2 = check(2 * i + 1);
        if(!r1 && !r2) {
            printf("IMPOSSIBLE\n");
            return 0;
        }else if(r1 && r2) {
            result[i] = 2;
        }else if(r1) {
            result[i] = 1;
        }else {
            result[i] = 0;
        }
    }
    for(int i = 1;i <= N;i++) {
        if(result[i] == 0) {
            printf("Y");
        }else if(result[i] == 1) {
            printf("N");
        }else {
            printf("?");
        }
    }
    printf("\n");
    return 0;
}
