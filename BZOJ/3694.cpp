#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 4010;
const int MAXM = 200010;
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

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v,int w) {
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
} graph;

int depths[MAXN],sizes[MAXN],tops[MAXN],fathers[MAXN],heavySons[MAXN],mapedIndexs[MAXN],dis[MAXN],nowTime;
int lc[MAXN << 2],rc[MAXN << 2],mv[MAXN << 2],left,right,root,nS;

void getTreeInfo(int now,int father) {
    fathers[now] = father;
    depths[now] = depths[father] + 1;
    sizes[now] = 1;
    int nowHeavySon = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
        getTreeInfo(tmpEdge.to,now);
        if(nowHeavySon == 0 || sizes[nowHeavySon] < sizes[tmpEdge.to]) {
            nowHeavySon = tmpEdge.to;
        }
        sizes[now] += sizes[tmpEdge.to];
    }
    heavySons[now] = nowHeavySon;
}

void mapIndex(int now,int father,int anc) {
    mapedIndexs[now] = ++nowTime;
    tops[now] = anc;
    if(heavySons[now] != 0) {
        mapIndex(heavySons[now],now,anc);
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || tmpEdge.to == heavySons[now]) continue;
        mapIndex(tmpEdge.to,now,tmpEdge.to);
    }
}

int newNode() {
    int sign = ++nS;
    lc[sign] = 0;
    rc[sign] = 0;
    mv[sign] = INF;
    return sign;
}

void upd(int now) {
    mv[now] = min(mv[lc[now]],mv[rc[now]]);
}

int buildTree(int left,int right) {
    if(left == right) return newNode();
    int mid = (left + right) >> 1,now = newNode();
    lc[now] = buildTree(left,mid);
    rc[now] = buildTree(mid + 1,right);
    return now;
}

void build() {
    getTreeInfo(1,0);
    mapIndex(1,0,1);
    left = 1; right = nowTime;
    root = buildTree(left,right);
}

void update(int now,int left,int right,int l,int r,int value) {
    if(left == l && right == r) {
        mv[now] = min(mv[now],value);
        return;
    }
    int mid = (left + right) >> 1;
    if(l <= mid) {
        if(r <= mid) {
            update(lc[now],left,mid,l,r,value);
        }else {
            update(lc[now],left,mid,l,mid,value);
            update(rc[now],mid + 1,right,mid + 1,r,value);
        }
    }else {
        update(rc[now],mid + 1,right,l,r,value);
    }
}

void update(int l,int r,int value) {
    update(root,left,right,l,r,value);
}

int getMin(int now,int left,int right,int pos) {
    if(left == right) return mv[now];
    int mid = (left + right) >> 1;
    if(pos <= mid) {
        return min(mv[now],getMin(lc[now],left,mid,pos));
    }else {
        return min(mv[now],getMin(rc[now],mid + 1,right,pos));
    }
}

int getMin(int pos) {
    return getMin(root,left,right,pos);
}

void updateMin(int u,int v,int value) {
    int topU = tops[u],topV = tops[v];
    while(topU != topV) {
        if(depths[topU] < depths[topV]) {
            swap(u,v);
            swap(topU,topV);
        }
        update(mapedIndexs[topU],mapedIndexs[u],value);
        u = fathers[topU];
        topU = tops[u];
    }
    if(u == v) return;
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    update(mapedIndexs[heavySons[v]],mapedIndexs[u],value);
}

struct Info {
    int u,v,w;
    Info() : u(0) , v(0) , w(0) { }
    Info(int u,int v,int w) : u(u) , v(v) , w(w) { }
} infos[MAXM];

int main() {
    int n = read<int>(),m = read<int>();
    int nowCnt = 0;
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>(),t = read<int>();
        if(t == 1) {
            graph.addTwoEdges(u,v,w);
        }else {
            infos[nowCnt++] = Info(u,v,w);
        }
    }
    build();
    for(int i = 0;i < nowCnt;i++) {
        Info &tmpInfo = infos[i];
        int value = dis[tmpInfo.u] + dis[tmpInfo.v] + tmpInfo.w;
        updateMin(tmpInfo.u,tmpInfo.v,value);
    }
    for(int i = 2;i <= n;i++) {
        int nowDis = getMin(mapedIndexs[i]);
        if(nowDis == INF) {
            printf("-1 ");
        }else {
            printf("%d ",nowDis - dis[i]);
        }
    }
    printf("\n");
    return 0;
}
