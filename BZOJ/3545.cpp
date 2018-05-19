#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_DEPTH = 21;
const int MAXN = 200010;
const int MAXM = 500010;
const int MAX_SEGMENT_NODE_SIZE = 4e6;

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
    Edge edges[MAXN];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

int N,M,Q;

struct BCS {
    int father[MAXN];

    void init(int size) {
        for(int i = 1;i <= size;i++) father[i] = i;
    }

    int getFather(int now) {
        if(now == father[now]) return now;
        father[now] = getFather(father[now]);
        return father[now];
    }

    void merge(int u,int v) {
        u = getFather(u);
        v = getFather(v);
        if(u == v) return;
        father[u] = v;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
} bcset;

int values[MAXN],sortedValues[MAXN],fathers[MAXN][MAX_DEPTH + 1],maxValue[MAXN],childSize,childs[MAXN],startSign[MAXN],endSign[MAXN];

struct Edge {
    int u,v,w;

    bool operator < (const Edge &otherEdge) const {
        return w < otherEdge.w;
    }
} edges[MAXM];

void dfs(int now,int father) {
    startSign[now] = childSize;
    if(graph.heads[now] == -1) {
        childs[++childSize] = now;
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        dfs(tmpEdge.to,now);
    }
    endSign[now] = childSize;
}

struct SegmentNode {
    int ch[2],cnt;

    SegmentNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root,left,right;

    SegmentTree() : root(0) , left(0) , right(0) { }

    SegmentTree(int left,int right) : root(newNode()) , left(left) , right(right) { }

    SegmentTree(int root,int left,int right) : root(newNode(root)) , left(left) , right(right) { }

    int newNode() {
        return newNode(0);
    }

    int newNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    void insert(int pos) {
        insert(root,left,right,pos);
    }

    void insert(int now,int left,int right,int pos) {
        sn[now].cnt++;
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = newNode(sn[now].ch[0]);
            insert(sn[now].ch[0],left,mid,pos);
        }else {
            sn[now].ch[1] = newNode(sn[now].ch[1]);
            insert(sn[now].ch[1],mid + 1,right,pos);
        }
    }

    static int getKth(const SegmentTree &now,const SegmentTree &prev,int k) {
        return getKth(now.root,prev.root,now.left,now.right,k);
    }

    static int getKth(int now,int prev,int left,int right,int k) {
        if(left == right) return left;
        int mid = (left + right) >> 1,cnt = sn[sn[now].ch[1]].cnt - sn[sn[prev].ch[1]].cnt;
        if(cnt >= k) {
            return getKth(sn[now].ch[1],sn[prev].ch[1],mid + 1,right,k);
        }else {
            return getKth(sn[now].ch[0],sn[prev].ch[0],left,mid,k - cnt);
        }
    }

    SegmentTree copy() {
        return SegmentTree(root,left,right);
    }
};

SegmentTree strees[MAXN];

void init() {
    for(int depth = 1;depth <= MAX_DEPTH;depth++) {
        for(int i = 1;i < 2 * N;i++) {
            fathers[i][depth] = fathers[fathers[i][depth - 1]][depth - 1];
        }
    }
}

int main() {
    N = read<int>();
    M = read<int>();
    Q = read<int>();
    bcset.init(N * 2);
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
        sortedValues[i] = values[i];
    }
    sort(sortedValues + 1,sortedValues + N + 1);
    int sortedSize = unique(sortedValues + 1,sortedValues + N + 1) - (sortedValues + 1);
    for(int i = 1;i <= N;i++) {
        values[i] = lower_bound(sortedValues + 1,sortedValues + sortedSize + 1,values[i]) - sortedValues;
    }
    for(int i = 1;i <= M;i++) {
        edges[i].u = read<int>();
        edges[i].v = read<int>();
        edges[i].w = read<int>();
    }
    sort(edges + 1,edges + M + 1);
    int nowSign = N + 1;
    for(int i = 1;i <= M;i++) {
        Edge &tmpEdge = edges[i];
        if(!bcset.isLinked(tmpEdge.u,tmpEdge.v)) {
            int u = bcset.getFather(tmpEdge.u),v = bcset.getFather(tmpEdge.v);
            graph.addEdge(nowSign,u);
            graph.addEdge(nowSign,v);
            bcset.merge(u,nowSign);
            bcset.merge(v,nowSign);
            fathers[u][0] = nowSign;
            fathers[v][0] = nowSign;
            maxValue[nowSign] = tmpEdge.w;
            nowSign++;
            if(nowSign == 2 * N) break;
        }
    }
    int root = nowSign - 1;
    init();
    dfs(root,0);
    strees[0] = SegmentTree(1,sortedSize);
    for(int i = 1;i <= childSize;i++) {
        strees[i] = strees[i - 1].copy();
        strees[i].insert(values[childs[i]]);
    }
    while(Q--) {
        int v = read<int>(),x = read<int>(),k = read<int>();
        int now = v;
        for(int i = MAX_DEPTH;i >= 0;i--) {
            if(fathers[now][i] != 0 && maxValue[fathers[now][i]] <= x) {
                now = fathers[now][i];
            }
        }
        if(k > endSign[now] - startSign[now]) {
            printf("-1\n");
            continue;
        }
        printf("%d\n",sortedValues[SegmentTree::getKth(strees[endSign[now]],strees[startSign[now]],k)]);
    }
    return 0;
}
