#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 80010;
const int MAX_DEPTH = 17;
const int MAX_SEGMENT_NODE_SIZE = 21280010;
const int BUFFER_SIZE = 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BCS {
    int *father,*rank;

    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) {
            father[i] = i;
        }
        rank = new int[size];
        fill(rank,rank + size,1);
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        u = getFather(u);
        v = getFather(v);
        if(u == v) return;
        if(rank[u] < rank[v]) {
            rank[v] += rank[u];
            father[u] = v;
        }else {
            rank[u] += rank[v];
            father[v] = u;
        }
    }

    int getSize(int pos) {
        return rank[getFather(pos)];
    }

} bcset(MAXN);

struct Graph {
    struct Edge {
        int next,to;
    } *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
} graph(MAXN * 2,MAXN);

int n,m,T,values[MAXN],sortedValues[MAXN],fathers[MAXN][MAX_DEPTH + 1],depth[MAXN];
bool visit[MAXN];
char buffer[BUFFER_SIZE];

struct SegmentNode {
    int cnt,ch[2];
    SegmentNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root;

    static int newNode() {
        sn[++segmentSize] = SegmentNode();
        return segmentSize;
    }

    static int copyNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    SegmentTree() {
        root = newNode();
    }

    SegmentTree(int root) : root(root) { }

    void insert(int pos) {
        insert(root,0,n - 1,pos);
    }

    void insert(int now,int left,int right,int pos) {
        sn[now].cnt++;
        if(left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = copyNode(sn[now].ch[0]);
            insert(sn[now].ch[0],left,mid,pos);
        }else {
            sn[now].ch[1] = copyNode(sn[now].ch[1]);
            insert(sn[now].ch[1],mid + 1,right,pos);
        }
    }

    static int getKth(const SegmentTree &u,const SegmentTree &v,const SegmentTree &lca,const SegmentTree &lcaFa,int k) {
        return getKth(u.root,v.root,lca.root,lcaFa.root,0,n - 1,k);
    }

    static int getKth(int u,int v,int lca,int lcaFa,int left,int right,int k) {
        if(left == right) {
            return left;
        }
        int mid = (left + right) >> 1,cnt = sn[sn[u].ch[0]].cnt + sn[sn[v].ch[0]].cnt - sn[sn[lca].ch[0]].cnt - sn[sn[lcaFa].ch[0]].cnt;
        if(cnt < k) {
            return getKth(sn[u].ch[1],sn[v].ch[1],sn[lca].ch[1],sn[lcaFa].ch[1],mid + 1,right,k - cnt);
        }else {
            return getKth(sn[u].ch[0],sn[v].ch[0],sn[lca].ch[0],sn[lcaFa].ch[0],left,mid,k);
        }
    }

    SegmentTree copy() {
        return SegmentTree(copyNode(root));
    }
};

SegmentTree strees[MAXN];

void dfs(int now,int father) {
    visit[now] = true;
    strees[now] = strees[father].copy();
    strees[now].insert(values[now]);
    depth[now] = depth[father] + 1;
    fathers[now][0] = father;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now);
    }
}

int getLCA(int u,int v) {
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depth[fathers[u][i]] >= depth[v]) {
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
    int testCase = read<int>();
    n = read<int>();m = read<int>();T = read<int>();
    for(int i = 1;i <= n;i++) {
        values[i] = read<int>();
        sortedValues[i - 1] = values[i];
    }
    sort(sortedValues,sortedValues + n);
    int nowSize = unique(sortedValues,sortedValues + n) - sortedValues;
    for(int i = 1;i <= n;i++) {
        values[i] = lower_bound(sortedValues,sortedValues + nowSize,values[i]) - sortedValues;
    }
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
        bcset.merge(u,v);
    }
    for(int i = 0;i < n;i++) {
        if(visit[i]) continue;
        dfs(i,0);
    }
    int lastAns = 0;
    while(T--) {
        scanf("%s",buffer);
        if(buffer[0] == 'Q') {
            int x = read<int>(),y = read<int>(),k = read<int>();
            x ^= lastAns;
            y ^= lastAns;
            k ^= lastAns;
            int lca = getLCA(x,y);
            lastAns = sortedValues[SegmentTree::getKth(strees[x],strees[y],strees[lca],strees[fathers[lca][0]],k)];
            printf("%d\n",lastAns);
        }else {
            int x = read<int>(),y = read<int>();
            x ^= lastAns;
            y ^= lastAns;
            graph.addEdge(x,y);
            graph.addEdge(y,x);
            int sizeX = bcset.getSize(x),sizeY = bcset.getSize(y);
            if(sizeX < sizeY) {
                dfs(x,y);
            }else {
                dfs(y,x);
            }
            bcset.merge(x,y);
        }
    }
    return 0;
}
