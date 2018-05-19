#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 17199267;
const int MAXN = 80002;
const int MAX_DEPTH = 17;

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

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph;

struct SegmentNode {
    int ch[2],cnt;

    SegmentNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0,left,right;

struct SegmentTree {
    int root;

    SegmentTree() : root(0) { }

    SegmentTree(int root) : root(newNode(root)) { }

    int newNode() {
        return newNode(0);
    }

    int newNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    void init() {
        root = newNode();
    }

    void updateCopy(int pos,int value) {
        updateCopy(root,left,right,pos,value);
    }

    void updateCopy(int now,int left,int right,int pos,int value) {
        sn[now].cnt += value;
        if(left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = newNode(sn[now].ch[0]);
            updateCopy(sn[now].ch[0],left,mid,pos,value);
        }else {
            sn[now].ch[1] = newNode(sn[now].ch[1]);
            updateCopy(sn[now].ch[1],mid + 1,right,pos,value);
        }
    }

    void update(int pos,int value) {
        update(root,left,right,pos,value);
    }

    void update(int now,int left,int right,int pos,int value) {
        sn[now].cnt += value;
        if(left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            if(sn[now].ch[0] == 0) {
                sn[now].ch[0] = newNode();
            }
            update(sn[now].ch[0],left,mid,pos,value);
        }else {
            if(sn[now].ch[1] == 0) {
                sn[now].ch[1] = newNode();
            }
            update(sn[now].ch[1],mid + 1,right,pos,value);
        }
    }

    SegmentTree copy() {
        return SegmentTree(root);
    }
};

int minRoots[MAXN],addRoots[MAXN],minIndex,addIndex;

struct BIT {
    SegmentTree strees[MAXN];

    int size;

    void init(int size) {
        this->size = size;
        for(int i = 1;i <= size;i++) {
            strees[i].init();
        }
    }

    void update(int x,int pos,int value) {
        for(int i = x;i <= size;i += lowbit(i)) {
            strees[i].update(pos,value);
        }
    }

    void getMin(int pos) {
        while(pos) {
            minRoots[minIndex++] = strees[pos].root;
            pos -= lowbit(pos);
        }
    }

    void getAdd(int pos) {
        while(pos) {
            addRoots[addIndex++] = strees[pos].root;
            pos -= lowbit(pos);
        }
    }

    int lowbit(int value) {
        return value & -value;
    }

} bitree;

struct Info {
    int k,a,b;

    Info() : k(0) , a(0) , b(0) { }
    Info(int k,int a,int b) : k(k) , a(a) , b(b) { }
} infos[MAXN];

int fathers[MAXN][MAX_DEPTH + 1],values[MAXN],sortedValues[MAXN * 2],starts[MAXN],ends[MAXN],depths[MAXN],nowTime,sortedSize;

SegmentTree strees[MAXN];

void build(int now,int father) {
    strees[now] = strees[father].copy();
    strees[now].updateCopy(values[now],1);
    starts[now] = ++nowTime;
    fathers[now][0] = father;
    depths[now] = depths[father] + 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i - 1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        build(tmpEdge.to,now);
    }
    ends[now] = nowTime;
}

int getLCA(int u,int v) {
    if(u == v) return u;
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

int getDis(int u,int v,int lca) {
    return depths[u] + depths[v] - 2 * depths[lca] + 1;
}

int getKth(int u,int v,int lca,int lcaFa,int left,int right,int k) {
    if(left == right) {
        return left;
    }
    int mid = (left + right) >> 1,cnt = sn[sn[u].ch[1]].cnt + sn[sn[v].ch[1]].cnt - sn[sn[lca].ch[1]].cnt - sn[sn[lcaFa].ch[1]].cnt;
    for(int i = 0;i < minIndex;i++) {
        cnt -= sn[sn[minRoots[i]].ch[1]].cnt;
    }
    for(int i = 0;i < addIndex;i++) {
        cnt += sn[sn[addRoots[i]].ch[1]].cnt;
    }
    if(cnt >= k) {
        for(int i = 0;i < minIndex;i++) {
            minRoots[i] = sn[minRoots[i]].ch[1];
        }
        for(int i = 0;i < addIndex;i++) {
            addRoots[i] = sn[addRoots[i]].ch[1];
        }
        return getKth(sn[u].ch[1],sn[v].ch[1],sn[lca].ch[1],sn[lcaFa].ch[1],mid +1,right,k);
    }else {
        for(int i = 0;i < minIndex;i++) {
            minRoots[i] = sn[minRoots[i]].ch[0];
        }
        for(int i = 0;i < addIndex;i++) {
            addRoots[i] = sn[addRoots[i]].ch[0];
        }
        return getKth(sn[u].ch[0],sn[v].ch[0],sn[lca].ch[0],sn[lcaFa].ch[0],left,mid,k - cnt);
    }
}

int getKth(int u,int v,int lca,int lcaFa,int k) {
    return getKth(u,v,lca,lcaFa,left,right,k);
}

int main() {
    int N = read<int>(),Q = read<int>();
    bitree.init(N + 1);
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
        sortedValues[sortedSize++] = values[i];
    }
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    for(int i = 0;i < Q;i++) {
        int k = read<int>(),a = read<int>(),b = read<int>();
        infos[i] = Info(k,a,b);
        if(k == 0) {
            sortedValues[sortedSize++] = b;
        }
    }
    sort(sortedValues,sortedValues + sortedSize);
    sortedSize = unique(sortedValues,sortedValues + sortedSize) - sortedValues;
    left = 0; right = sortedSize - 1;
    for(int i = 1;i <= N;i++) {
        values[i] = lower_bound(sortedValues,sortedValues + sortedSize,values[i]) - sortedValues;
    }
    build(1,0);
    for(int i = 0;i < Q;i++) {
        Info &tmpInfo = infos[i];
        int k = tmpInfo.k,a = tmpInfo.a,b = tmpInfo.b;
        if(k == 0) {
            b = lower_bound(sortedValues,sortedValues + sortedSize,b) - sortedValues;
            bitree.update(starts[a],values[a],-1);
            bitree.update(ends[a] + 1,values[a],1);
            values[a] = b;
            bitree.update(starts[a],values[a],1);
            bitree.update(ends[a] + 1,values[a],-1);
        }else {
            int lca = getLCA(a,b),cnt = getDis(a,b,lca),lcaFa = fathers[lca][0];
            if(cnt < k) {
                printf("invalid request!\n");
            }else {
                minIndex = 0;
                addIndex = 0;
                bitree.getAdd(starts[a]);
                bitree.getAdd(starts[b]);
                bitree.getMin(starts[lca]);
                bitree.getMin(starts[lcaFa]);
                printf("%d\n",sortedValues[getKth(strees[a].root,strees[b].root,strees[lca].root,strees[fathers[lca][0]].root,k)]);
            }
        }
    }
    return 0;
}
