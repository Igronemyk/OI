#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int INF = INT_MAX;
const int MAXN = 10010;

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
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        clear();
    }

    void addEdge(int u,int v,int w) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
} graph;

int depth[MAXN],size[MAXN];
bool visit[MAXN];

void getDepth(int now,int father,int nowDepth,int &nowIndex) {
    for(int i = graph.heads[now];i != -1; i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        depth[nowIndex++] = nowDepth + tmpEdge.weight;
        getDepth(tmpEdge.to,now,nowDepth + tmpEdge.weight,nowIndex);
    }
}

int calc(int now,int limit) {
    int size = 1,result = 0;
    depth[now] = 0;
    depth[0] = 0;
    getDepth(now,-1,0,size);
    sort(depth,depth + size);
    int left = 0,right = size - 1;
    while(left < right) {
        if(depth[left] + depth[right] <= limit) {
            result += right - left;
            left++;
        }else {
            right--;
        }
    }
    return result;
}

void getCenter(int now,int father,int nowTreeSize,int &center,int &centerWeight) {
    size[now] = 1;
    int maxChildSize = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        getCenter(tmpEdge.to,now,nowTreeSize,center,centerWeight);
        size[now] += size[tmpEdge.to];
        maxChildSize = max(maxChildSize,size[tmpEdge.to]);
    }
    maxChildSize = max(maxChildSize,nowTreeSize - size[now]);
    if(centerWeight > maxChildSize) {
        center = now;
        centerWeight = maxChildSize;
    }
}

void solve(int now,int limit,int &result) {
    visit[now] = true;
    result += calc(now,limit);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        result -= calc(tmpEdge.to,limit - 2 * tmpEdge.weight);
        int root = -1,rootWeight = INF;
        getCenter(tmpEdge.to,-1,size[tmpEdge.to],root,rootWeight);
        solve(root,limit,result);
    }
}

int main() {
    int n,k;
    while(~scanf("%d%d",&n,&k)) {
        if(n == 0 && k == 0) break;
        graph.clear();
        memset(depth,0,sizeof(depth));
        memset(size,0,sizeof(size));
        memset(visit,0,sizeof(visit));
        int root = -1,rootWeight = INF,result = 0;
        for(int i = 0;i < n - 1;i++) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            u--; v--;
            graph.addEdge(u,v,w);
            graph.addEdge(v,u,w);
        }
        getCenter(0,-1,n,root,rootWeight);
        solve(root,k,result);
        printf("%d\n",result);
    }
    return 0;
}
