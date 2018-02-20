#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int MAXN = 300010;
const int MAXM = 300010;
const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'a';

bool isCaled[MAXN],visit[MAXN],flag;
int mem[MAXN][MAX_CHARSET_SIZE];
int maxValue[MAXN];

int n,m;
string signs;

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() {
        clear();
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
} graph;


void dfs(int now) {
    if(isCaled[now]) return;
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) {
            flag = true;
            break;
        }
        dfs(tmpEdge.to);
        if(flag) break;
        for(int j = 0;j < MAX_CHARSET_SIZE;j++) {
            mem[now][j] = max(mem[now][j],mem[tmpEdge.to][j]);
        }
    }
    mem[now][signs[now - 1] - FIRST_CHAR]++;
    for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
        if(mem[now][maxValue[now]] < mem[now][i]) {
            maxValue[now] = i;
        }
    }
    visit[now] = false;
    isCaled[now] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    cin >> signs;
    for(int i = 0;i < m;i++) {
        int x,y;
        cin >> x >> y;
        graph.addEdge(x,y);
    }
    for(int i = 1;i <= n;i++) {
        if(!isCaled[i]) {
            dfs(i);
        }
        if(flag) {
            break;
        }
    }
    int result = 0;
    for(int i = 1;i <= n;i++) {
        result = max(result,mem[i][maxValue[i]]);
    }
    if(flag) {
        cout << -1 << endl;
    }else {
        cout << result << endl;
    }
    return 0;
}
