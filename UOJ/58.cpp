#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 100010;
const int MAXM = 100010;
const int MAXQ = 100010;
const int MAX_VALUE_SIZE = MAXN * 2;
const int MAX_DEPTH = 22;

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

int n,m,q,sqrtSize,optCnt,infoCnt,nowIndex,belong[MAX_VALUE_SIZE  + 1],types[MAXN],cnt[MAXM],eulerValues[MAX_VALUE_SIZE],starts[MAXN],ends[MAXN],depths[MAXN],fathers[MAXN][MAX_DEPTH + 1],initTypes[MAXN];
long long result,initWeights[MAXM],sumWeights[MAXN],results[MAXQ];
bool visit[MAXN];

struct Operation {
    int pos,oldValue,newValue;

    Operation() : pos(-1) , oldValue(-1) , newValue(-1) { }

    Operation(int pos,int oldValue,int newValue) : pos(pos) , oldValue(oldValue) , newValue(newValue) { }

} opts[MAXQ];

struct Info {
    int id,left,right,lca,time;

    Info() : id(-1) , left(-1) , right(-1) , lca(-1) , time(-1) { }

    Info(int id,int left,int right,int lca,int time) : id(id) , left(left) , right(right) , lca(lca) , time(time) { }

    bool operator < (const Info &otherInfo) const {
        if(belong[left] != belong[otherInfo.left]) return belong[left] < belong[otherInfo.left];
        if(belong[right] != belong[otherInfo.right]) return belong[right] < belong[otherInfo.right];
        return time < otherInfo.time;
    }
} infos[MAXQ];


void addCnt(int type) {
    result -= initWeights[type] * sumWeights[cnt[type]];
    cnt[type]++;
    result += initWeights[type] * sumWeights[cnt[type]];
}

void delCnt(int type) {
    result -= initWeights[type] * sumWeights[cnt[type]];
    cnt[type]--;
    result += initWeights[type] * sumWeights[cnt[type]];
}

void addOpt(int sign) {
    Operation &tmpOpt = opts[sign];
    if(visit[tmpOpt.pos]) {
        delCnt(types[tmpOpt.pos]);
    }
    types[tmpOpt.pos] = tmpOpt.newValue;
    if(visit[tmpOpt.pos]) {
        addCnt(types[tmpOpt.pos]);
    }
}

void revOpt(int sign) {
    Operation &tmpOpt = opts[sign];
    if(visit[tmpOpt.pos]) {
        delCnt(types[tmpOpt.pos]);
    }
    types[tmpOpt.pos] = tmpOpt.oldValue;
    if(visit[tmpOpt.pos]) {
        addCnt(types[tmpOpt.pos]);
    }
}

void change(int now) {
    if(visit[now]) {
        delCnt(types[now]);
    }else {
        addCnt(types[now]);
    }
    visit[now] = !visit[now];
}

void initBlock() {
    sqrtSize = pow(n,2.00 / 3.00);
    for(int i = 1;i <= MAX_VALUE_SIZE;i++) {
        belong[i] = i / sqrtSize;
    }
}

void dfs(int now,int father) {
    starts[now] = nowIndex;
    eulerValues[nowIndex++] = now;
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
    ends[now] = nowIndex;
    eulerValues[nowIndex++] = now;
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

int main() {
    n = read<int>(); m = read<int>(); q = read<int>();
    initBlock();
    for(int i = 1;i <= m;i++) {
        initWeights[i] = read<int>();
    }
    for(int i = 1;i <= n;i++) {
        sumWeights[i] = sumWeights[i - 1] + read<int>();
    }
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    dfs(1,0);
    for(int i = 1;i <= n;i++) {
        types[i] = read<int>();
        initTypes[i] = types[i];
    }
    for(int i = 0;i < q;i++) {
        int t = read<int>(),x = read<int>(),y = read<int>();
        if(t == 0) {
            opts[++optCnt] = Operation(x,types[x],y);
            types[x] = y;
        }else {
            if(starts[x] > starts[y]) {
                swap(x,y);
            }
            int lca = getLCA(x,y);
            if(lca != x) {
                infos[infoCnt] = Info(infoCnt,ends[x],starts[y],lca,optCnt);
            }else {
                infos[infoCnt] = Info(infoCnt,starts[x],starts[y],lca,optCnt);
            }
            infoCnt++;
        }
    }
    sort(infos,infos + infoCnt);
    int nowLeft = 0,nowRight = -1,nowTime = 0;
    memcpy(types,initTypes,sizeof(int) * n);
    for(int i = 0;i < infoCnt;i++) {
        Info &tmpInfo = infos[i];
        while(nowTime < tmpInfo.time) {
            nowTime++;
            addOpt(nowTime);
        }
        while(nowTime > tmpInfo.time) {
            revOpt(nowTime);
            nowTime--;
        }
        while(nowLeft > tmpInfo.left) {
            nowLeft--;
            change(eulerValues[nowLeft]);
        }
        while(nowRight < tmpInfo.right) {
            nowRight++;
            change(eulerValues[nowRight]);
        }
        while(nowLeft < tmpInfo.left) {
            change(eulerValues[nowLeft]);
            nowLeft++;
        }
        while(nowRight > tmpInfo.right) {
            change(eulerValues[nowRight]);
            nowRight--;
        }
        if(!visit[tmpInfo.lca]) {
            addCnt(types[tmpInfo.lca]);
        }
        results[tmpInfo.id] = result;
        if(!visit[tmpInfo.lca]) {
            delCnt(types[tmpInfo.lca]);
        }
    }
    for(int i = 0;i < infoCnt;i++) {
        printf("%lld\n",results[i]);
    }
    return 0;
}
