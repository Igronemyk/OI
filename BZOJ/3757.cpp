#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 50010;
const int MAXM = 100010;
const int MAX_DEPTH = 20;

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
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

int n,m;
int eulerValues[MAXN * 2],nowTime,starts[MAXN],ends[MAXN],fathers[MAXN][MAX_DEPTH + 1],depths[MAXN],colors[MAXN],cnt[MAXN],results[MAXM],result = 0;
bool visit[MAXN];

void dfs(int now,int father) {
    starts[now] = nowTime;
    eulerValues[nowTime++] = now;
    fathers[now][0] = father;
    depths[now] = depths[father] + 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now);
    }
    ends[now] = nowTime;
    eulerValues[nowTime++] = now;
}

int getLCA(int u,int v) {
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            u = fathers[u][i];
        }
    }
    if(u == v) return u;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            u = fathers[u][i];
            v = fathers[v][i];
        }
    }
    return fathers[u][0];
}

struct Info {
    int id,left,right,block,lca,a,b;

    Info() : id(-1) , left(-1) , right(-1) , block(-1) ,  lca(-1) , a(-1) , b(-1) { }

    Info(int id,int left,int right,int block,int lca,int a,int b) : id(id) , left(left) , right(right) , block(block) , lca(lca) , a(a) , b(b) { }

    bool operator < (const Info &otherInfo) const {
        if(block != otherInfo.block) {
            return block < otherInfo.block;
        }
        return right < otherInfo.right;
    }
} infos[MAXM];

void modify(int pos) {
    if(visit[pos]) {
        cnt[colors[pos]]--;
        if(cnt[colors[pos]] == 0) {
            result--;
        }
    }else {
        if(cnt[colors[pos]] == 0) {
            result++;
        }
        cnt[colors[pos]]++;
    }
    visit[pos] = !visit[pos];
}

int main() {
    n = read<int>();
    m = read<int>();
    for(int i = 1;i <= n;i++) {
        colors[i] = read<int>();
    }
    int root = 0;
    for(int i = 1;i <= n;i++) {
        int u = read<int>(),v = read<int>();
        if(u > v) {
            swap(u,v);
        }
        if(u == 0) {
            root = v;
            continue;
        }
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    dfs(root,0);
    int sqrtValue = static_cast<int>(sqrt(n * 2));
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(),a = read<int>(),b = read<int>();
        if(starts[u] > starts[v]) {
            swap(u,v);
        }
        int left,right,lca = getLCA(u,v);
        if(lca != u) {
            left = ends[u];
            right = starts[v];
        }else {
            left = starts[u];
            right = starts[v];
        }
        infos[i] = Info(i,left,right,left / sqrtValue,lca,a,b);
    }
    sort(infos,infos + m);
    int nowLeft = 0,nowRight = -1;
    for(int i = 0;i < m;i++) {
        Info &tmpInfo = infos[i];
        while(nowLeft > tmpInfo.left) {
            nowLeft--;
            modify(eulerValues[nowLeft]);
        }
        while(nowRight < tmpInfo.right) {
            nowRight++;
            modify(eulerValues[nowRight]);
        }
        while(nowLeft < tmpInfo.left) {
            modify(eulerValues[nowLeft]);
            nowLeft++;
        }
        while(nowRight > tmpInfo.right) {
            modify(eulerValues[nowRight]);
            nowRight--;
        }
        int tmpResult = result;
        if(!visit[tmpInfo.lca]) {
            if(cnt[colors[tmpInfo.lca]] == 0) {
                tmpResult++;
            }
            cnt[colors[tmpInfo.lca]]++;
        }
        if(tmpInfo.a != tmpInfo.b) {
            if(tmpInfo.a != 0 || tmpInfo.b != 0) {
                if(cnt[tmpInfo.a] > 0 && cnt[tmpInfo.b] > 0) {
                    tmpResult--;
                }
            }
        }
        if(!visit[tmpInfo.lca]) {
            cnt[colors[tmpInfo.lca]]--;
        }
        results[tmpInfo.id] = tmpResult;
    }
    for(int i = 0;i < m;i++) {
        printf("%d\n",results[i]);
    }
    return 0;
}
