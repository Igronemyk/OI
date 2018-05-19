#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAXM = 200010;
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
        int next,to,weight;
    };
    Edge edges[MAXM];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph;

int N,K,dis[MAXN],cnt[MAXN];
bool visit[MAXN];

bool spfa() {
    queue<int> que;
    for(int i = 1;i <= N;i++) {
        dis[i] = 1;
        visit[i] = true;
        que.push(i);
    }
    while(!que.empty()) {
        int now = que.front();
        que.pop();
        visit[now] = false;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[tmpEdge.to] >= dis[now] + tmpEdge.weight) continue;
            dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
            if(!visit[tmpEdge.to]) {
                visit[tmpEdge.to] = true;
                que.push(tmpEdge.to);
                cnt[tmpEdge.to]++;
                if(cnt[tmpEdge.to] > N) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    N = read<int>(); K = read<int>();
    while(K--) {
        int opt = read<int>(),A = read<int>(),B = read<int>();
        switch(opt) {
            case 1: {
                graph.addEdge(B,A,0);
                graph.addEdge(A,B,0);
                break;
            }
            case 2: {
                graph.addEdge(A,B,1);
                break;
            }
            case 3: {
                graph.addEdge(B,A,0);
                break;
            }
            case 4: {
                graph.addEdge(B,A,1);
                break;
            }
            case 5: {
                graph.addEdge(A,B,0);
                break;
            }
        }
    }
    bool result = spfa();
    if(!result) {
        printf("-1\n");
    }else {
        long long result = 0;
        for(int i = 1;i <= N;i++) {
            result += dis[i];
        }
        printf("%lld\n",result);
    }
    return 0;
}
