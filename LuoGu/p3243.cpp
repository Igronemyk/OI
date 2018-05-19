#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

const int MAXM = 100010;
const int MAXN = 100010;

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
    int tot,heads[MAXN],degree[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
        memset(degree,0,sizeof(degree));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
        degree[v]++;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
        memset(degree,0,sizeof(degree));
    }
} graph;

void clear() {
    graph.clear();
}

void solve() {
    int N = read<int>(),M = read<int>();
    while(M--) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(v,u);
    }
    set<int> values;
    for(int i = 1;i <= N;i++) {
        if(graph.degree[i] == 0) {
            values.insert(i);
        }
    }
    vector<int> results;
    while(!values.empty()) {
        int now = *values.rbegin();
        values.erase(--values.end());
        results.push_back(now);
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            graph.degree[tmpEdge.to]--;
            if(graph.degree[tmpEdge.to] == 0) {
                values.insert(tmpEdge.to);
            }
        }
    }
    if(results.size() != N) {
        printf("Impossible!\n");
    }else {
        for(vector<int>::reverse_iterator it = results.rbegin();it != results.rend();it++) {
            printf("%d ",*it);
        }
        printf("\n");
    }
}

int main() {
    int D = read<int>();
    while(D--) {
        clear();
        solve();
    }
    return 0;
}
