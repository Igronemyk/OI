#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

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
    Edge edges[MAXN * MAXN];
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

int values[MAXN],minValues[MAXN],color[MAXN];

bool dfs(int now) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(color[tmpEdge.to] != 0) {
            if(color[tmpEdge.to] == color[now]) return false;
            continue;
        }
        if(color[now] == 1) {
            color[tmpEdge.to] = 2;
        }else {
            color[tmpEdge.to] = 1;
        }
        bool result = dfs(tmpEdge.to);
        if(!result) return false;
    }
    return true;
}

int main() {
    int n = read<int>();
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
    }
    minValues[n + 1] = INF;
    for(int i = n;i >= 1;i--) {
        minValues[i] = min(minValues[i + 1],values[i]);
    }
    for(int i = 1;i <= n;i++) {
        for(int j = i + 1;j <= n;j++) {
            if(values[i] < values[j] && values[i] > minValues[j + 1]) {
                graph.addEdge(i,j);
                graph.addEdge(j,i);
            }
        }
    }
    bool flag = false;
    for(int i = 1;i <= n;i++) {
        if(color[i] == 0) {
            color[i] = 1;
            if(!dfs(i)) {
                flag = true;
                break;
            }
        }
    }
    if(flag) {
        printf("0\n");
        return 0;
    }
    int nowIndex = 1;
    stack<int> stk[3];
    for(int i = 1;i <= n;i++) {
        stk[color[i]].push(values[i]);
        if(color[i] == 1) {
            printf("a ");
        }else {
            printf("c ");
        }
        for(int j = 1;j <= 2;j++) {
            while(!stk[j].empty() && stk[j].top() == nowIndex) {
                stk[j].pop();
                nowIndex++;
                if(j == 1) {
                    printf("b ");
                }else {
                    printf("d ");
                }
            }
        }
    }
    for(int i = 1;i <= 2;i++) {
        while(!stk[i].empty()) {
            stk[i].pop();
            if(i == 1) {
                printf("b ");
            }else {
                printf("d ");
            }
        }
    }
    printf("\n");
    return 0;
}
