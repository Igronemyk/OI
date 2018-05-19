#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <functional>
#include <vector>

using namespace std;

const int MAXM = 70010;
const int MAXN = 3010;
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
        int next,to,weight;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() {
        memset(heads,-1,sizeof(heads));
    }
    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }

} graph;

int N,M,dis1[MAXN],dis2[MAXN],cnt[MAXN];
bool visit[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
vector<int> links[MAXN];

void dijkstra(int start) {
    memset(dis1,INF,sizeof(dis1));
    dis1[start] = 0;
    pq.push(make_pair(dis1[start],start));
    while(!pq.empty()) {
        pair<int,int> tmpValue = pq.top();
        int now = tmpValue.second;
        pq.pop();
        if(visit[now]) continue;
        visit[now] = true;
        int nowDist = max(dis1[now],dis2[now]);
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis1[tmpEdge.to] <= nowDist + tmpEdge.weight) continue;
            dis1[tmpEdge.to] = nowDist + tmpEdge.weight;
            int tmpValue = max(dis1[tmpEdge.to],dis2[tmpEdge.to]);
            if(cnt[tmpEdge.to] == 0) {
                pq.push(make_pair(tmpValue,tmpEdge.to));
            }
        }
        for(vector<int>::iterator it = links[now].begin();it != links[now].end();it++) {
            int v = *it;
            cnt[v]--;
            dis2[v] = max(dis2[v],nowDist);
            int tmpValue = max(dis1[v],dis2[v]);
            if(cnt[v] == 0) {
                pq.push(make_pair(tmpValue,v));
            }
        }
    }

}


int main() {
    N = read<int>(); M = read<int>();
    for(int i = 0;i < M;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,w);
    }
    for(int i = 1;i <= N;i++) {
        int tmpCnt = read<int>();
        cnt[i] = tmpCnt;
        for(int j = 0;j < tmpCnt;j++) {
            int tmpValue = read<int>();
            links[tmpValue].push_back(i);
        }
    }
    dijkstra(1);
    printf("%d\n",max(dis1[N],dis2[N]));
    return 0;
}
