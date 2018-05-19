#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 110;

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

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

} graph;

int color[MAXN],nowIndex;
bool dp[MAXN][MAXN * 2];
bool visit[MAXN][MAXN],graph1[MAXN][MAXN];
vector<int> teams[MAXN][2];

bool dfs(int now) {
    teams[nowIndex][color[now]].push_back(now);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(color[tmpEdge.to] != -1) {
            if(color[tmpEdge.to] == color[now]) return false;
            continue;
        }
        color[tmpEdge.to] = color[now] ^ 1;
        dfs(tmpEdge.to);
    }
    return true;
}

void init() {
    graph.clear();
    memset(color,-1,sizeof(color));
    memset(graph1,0,sizeof(graph1));
    nowIndex = 0;
    memset(dp,0,sizeof(dp));
    memset(visit,0,sizeof(visit));
}

int N;

int solve() {
    init();
    for(int i = 1;i <= N;i++) {
        int now = 0;
        while((now = read<int>()) != 0) {
            visit[i][now] = true;
        }
    }
    for(int i = 1;i <= N;i++) {
        for(int j = 1;j <= N;j++) {
            if(i == j) continue;
            if(!visit[i][j]) {
                graph1[i][j] = true;
                graph1[j][i] = true;
            }
        }
    }
    for(int i = 1;i <= N;i++) {
        for(int j = i + 1;j <= N;j++) {
            if(graph1[i][j]) {
                graph.addEdge(i,j);
                graph.addEdge(j,i);
            }
        }
    }
    int maxState = N * 2;
    dp[0][N] = true;
    for(int i = 1;i <= N;i++) {
        if(color[i] != -1) continue;
        color[i] = 0;
        teams[nowIndex][0].clear();
        teams[nowIndex][1].clear();
        if(!dfs(i)) {
            printf("No solution\n");
            return 0;
        }
        nowIndex++;
        int delta = abs(static_cast<int>(teams[nowIndex - 1][0].size()) - static_cast<int>(teams[nowIndex - 1][1].size()));
        for(int j = 0;j <= maxState;j++) {
            if(!dp[nowIndex - 1][j]) continue;
            int to1 = j + delta,to2 = j - delta;
            if(to1 <= maxState && to1 >= 0) {
                dp[nowIndex][to1] = true;
            }
            if(to2 <= maxState && to2 >= 0) {
                dp[nowIndex][to2] = true;
            }
        }
    }
    vector<int> team[2];
    for(int absValue = 0;absValue <= N;absValue++) {
        if(dp[nowIndex][N + absValue]) {
            int nowValue = N + absValue;
            for(int i = nowIndex - 1;i >= 0;i--) {
                int delta = static_cast<int>(teams[i][0].size()) - static_cast<int>(teams[i][1].size());
                if(dp[i][nowValue + delta]) {
                    team[0].insert(team[0].end(),teams[i][0].begin(),teams[i][0].end());
                    team[1].insert(team[1].end(),teams[i][1].begin(),teams[i][1].end());
                    nowValue += delta;
                }else {
                    team[0].insert(team[0].end(),teams[i][1].begin(),teams[i][1].end());
                    team[1].insert(team[1].end(),teams[i][0].begin(),teams[i][0].end());
                    nowValue -= delta;
                }
            }
            break;
        }
        if(dp[nowIndex][N - absValue]) {
            int nowValue = N - absValue;
            for(int i = nowIndex - 1;i >= 0;i--) {
                int delta = static_cast<int>(teams[i][0].size()) - static_cast<int>(teams[i][1].size());
                if(dp[i][nowValue + delta]) {
                    team[0].insert(team[0].end(),teams[i][0].begin(),teams[i][0].end());
                    team[1].insert(team[1].end(),teams[i][1].begin(),teams[i][1].end());
                    nowValue += delta;
                }else {
                    team[0].insert(team[0].end(),teams[i][1].begin(),teams[i][1].end());
                    team[1].insert(team[1].end(),teams[i][0].begin(),teams[i][0].end());
                    nowValue -= delta;
                }
            }
            break;
        }
    }
    if(team[0].size() == 0 || team[1].size() == 0) {
        printf("No solution\n");
        return 0;
    }
    for(int i = 0;i < 2;i++) {
        printf("%d ",static_cast<int>(team[i].size()));
        for(vector<int>::iterator it = team[i].begin();it != team[i].end();it++) {
            printf("%d ",*it);
        }
        printf("\n");
    }
    return 0;
}

int main() {
    while(~scanf("%d",&N)) {
        solve();
    }
    return 0;
}
