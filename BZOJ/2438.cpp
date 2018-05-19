#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAXM = 300010;
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
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }

} graph,newGraph;

int low[MAXN],dfn[MAXN],nowIndex,nowCnt,sccSize[MAXN],belong[MAXN],degree[MAXN];
bool inStack[MAXN];
stack<int> stk;

void tarjan(int now,int father) {
    dfn[now] = low[now] = ++nowIndex;
    inStack[now] = true;
    stk.push(now);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(!dfn[tmpEdge.to]) {
            tarjan(tmpEdge.to,now);
            low[now] = min(low[now],low[tmpEdge.to]);
        }else if(inStack[tmpEdge.to]) {
            low[now] = min(low[now],low[tmpEdge.to]);
        }
    }
    if(low[now] == dfn[now]) {
        int tmp;
        do{
            tmp = stk.top();
            stk.pop();
            belong[tmp] = nowCnt;
            sccSize[nowCnt]++;
            inStack[tmp] = false;
        }while(tmp != now);
        nowCnt++;
    }
}

pair<int,int> values[MAXM];

int main() {
    int N = read<int>(),M = read<int>();
    for(int i = 0;i < M;i++) {
        int x = read<int>(),y = read<int>();
        graph.addEdge(x,y);
        values[i] = make_pair(x,y);
    }
    for(int i = 1;i <= N;i++) {
        if(!dfn[i]) {
            tarjan(i,0);
        }
    }
    for(int i = 0;i < M;i++) {
        pair<int,int> &tmpEdge = values[i];
        if(belong[tmpEdge.first] != belong[tmpEdge.second]) {
            degree[belong[tmpEdge.second]]++;
            newGraph.addEdge(belong[tmpEdge.first],belong[tmpEdge.second]);
        }
    }
    int result = 0;
    for(int i = 0;i < nowCnt;i++) {
        if(degree[i] == 0) {
            result++;
        }
    }
    for(int i = 0;i < nowCnt;i++) {
        if(sccSize[i] != 1) continue;
        if(degree[i] != 0) continue;
        bool flag = true;
        for(int j = newGraph.heads[i];j != -1;j = newGraph.edges[j].next) {
            Graph::Edge &tmpEdge = newGraph.edges[j];
            if(degree[tmpEdge.to] <= 1) {
                flag = false;
                break;
            }
        }
        if(flag) {
            result--;
            break;
        }
    }
    printf("%.6lf\n",(N - result) * 1.00 / N);
    return 0;
}
