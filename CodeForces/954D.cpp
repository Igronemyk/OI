#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#include <utility>

using namespace std;

const int MAXN = 1010;
const int MAXM = 1010;
const int INF = 0x3f3f3f3f;

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge edges[MAXM * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
} graph;

int n,m;

void spfa(int *dis,bool *visit,int s,int t) {
    memset(dis,INF,sizeof(int) * n);
    memset(visit,false,sizeof(bool) * n);
    queue<int> que;
    dis[s] = 0;
    que.push(s);
    while(!que.empty()) {
        int tmp = que.front();
        que.pop();
        visit[tmp] = false;
        for(int i = graph.heads[tmp];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[tmpEdge.to] > dis[tmp] + 1) {
                dis[tmpEdge.to] = dis[tmp] + 1;
                if(!visit[tmpEdge.to]) {
                    que.push(tmpEdge.to);
                    visit[tmpEdge.to] = true;
                }
            }
        }
    }
}

int calc(int value) {
    if(value < 2) return 0;
    return (value * (value - 1)) / 2;
}

bool isLinked[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    int s,t;
    cin >> s >> t;
    s--; t--;
    vector<pair<int,int> >edges;
    for(int i = 0;i < m;i++) {
        int u,v;
        cin >> u >> v;
        u--; v--;
        isLinked[u][v] = true;
        isLinked[v][u] = true;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
        edges.push_back(make_pair(u,v));
    }
    bool *visit = new bool[n];
    int *dis1 = new int[n],*dis2 = new int[n];
    spfa(dis1,visit,s,t);
    spfa(dis2,visit,t,s);
    int minDis = dis1[t];
    int cnt = 0;
    for(int i = 0;i < n;i++) {
        for(int j = i + 1;j < n;j++) {
            if(isLinked[i][j]) continue;
            if(dis1[i] + dis2[j] + 1 < minDis) {
                continue;
            }
            if(dis2[i] + dis1[j] + 1 < minDis) {
                continue;
            }
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}

