#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

namespace SegmentTree {
    int lc[MAXN << 2],rc[MAXN << 2],add[MAXN << 2],same[MAXN << 2],mx[MAXN << 2],sZ;
    struct SegmentTree {
        int rt,l,r;

        SegmentTree() : rt(0) { }
        SegmentTree(int l,int r,int *values) : rt(build(l,r,values)) , l(l) , r(r) { }

        int newNode(int value) {
            int sign = ++sZ;
            lc[sign] = 0;
            rc[sign] = 0;
            add[sign] = 0;
            same[sign] = -1;
            mx[sign] = value;
            return sign;
        }

        int newNode() {
            return newNode(0);
        }

        void upd(int now) {
            mx[now] = max(mx[lc[now]],mx[rc[now]]);
        }

        void updSame(int now,int value) {
            if(now == 0) return;
            mx[now] = value;
            if(lc[now] != 0 && rc[now] != 0) {
                same[now] = value;
                add[now] = 0;
            }
        }

        void updAdd(int now,int value) {
            if(now == 0) return;
            mx[now] += value;
            if(lc[now] != 0 && rc[now] != 0) {
                if(same[now] != -1) {
                    same[now] += value;
                }else {
                    add[now] += value;
                }
            }
        }

        void pd(int now) {
            if(same[now] != -1) {
                updSame(lc[now],same[now]);
                updSame(rc[now],same[now]);
                same[now] = -1;
            }
            if(add[now] != 0) {
                updAdd(lc[now],add[now]);
                updAdd(rc[now],add[now]);
                add[now] = 0;
            }
        }

        int build(int l,int r,int *values) {
            if(l == r) return newNode(values[l]);
            int mid = (l + r) >> 1,now = newNode();
            lc[now] = build(l,mid,values);
            rc[now] = build(mid + 1,r,values);
            upd(now);
            return now;
        }

        void makeSame(int ql,int qr,int value) {
            makeSame(rt,l,r,ql,qr,value);
        }

        void makeSame(int now,int l,int r,int ql,int qr,int value) {
            if(ql == l && qr == r) {
                updSame(now,value);
                return;
            }
            pd(now);
            int mid = (l + r) >> 1;
            if(ql <= mid) {
                if(qr <= mid) {
                    makeSame(lc[now],l,mid,ql,qr,value);
                }else {
                    makeSame(lc[now],l,mid,ql,mid,value);
                    makeSame(rc[now],mid + 1,r,mid + 1,qr,value);
                }
            }else {
                makeSame(rc[now],mid + 1,r,ql,qr,value);
            }
            upd(now);
        }

        void addVal(int ql,int qr,int value) {
            addVal(rt,l,r,ql,qr,value);
        }

        void addVal(int now,int l,int r,int ql,int qr,int value) {
            if(ql == l && qr == r) {
                updAdd(now,value);
                return;
            }
            pd(now);
            int mid = (l + r) >> 1;
            if(ql <= mid) {
                if(qr <= mid) {
                    addVal(lc[now],l,mid,ql,qr,value);
                }else {
                    addVal(lc[now],l,mid,ql,mid,value);
                    addVal(rc[now],mid + 1,r,mid + 1,qr,value);
                }
            }else {
                addVal(rc[now],mid + 1,r,ql,qr,value);
            }
            upd(now);
        }

        int getMax(int ql,int qr) {
            return getMax(rt,l,r,ql,qr);
        }

        int getMax(int now,int l,int r,int ql,int qr) {
            if(ql == l && qr == r) {
                return mx[now];
            }
            pd(now);
            int mid = (l + r) >> 1;
            if(ql <= mid) {
                if(qr <= mid) {
                    return getMax(lc[now],l,mid,ql,qr);
                }else {
                    return max(getMax(lc[now],l,mid,ql,mid),getMax(rc[now],mid + 1,r,mid + 1,qr));
                }
            }else {
                return getMax(rc[now],mid + 1,r,ql,qr);
            }
        }

    };
}

namespace Tree {
    struct Graph {
        struct Edge {
            int next,to,weight,sign;
        };
        Edge edges[MAXN * 2];
        int tot,heads[MAXN];

        Graph() : tot(0) {
            memset(heads,-1,sizeof(heads));
        }

        void addEdge(int u,int v,int w,int sign) {
            edges[tot].next = heads[u];
            edges[tot].to = v;
            edges[tot].weight = w;
            edges[tot].sign = sign;
            heads[u] = tot++;
        }
    } graph;

    int depths[MAXN],fathers[MAXN],sons[MAXN],values[MAXN],mapedValues[MAXN],tops[MAXN],sizes[MAXN],mapedIndexs[MAXN],edgesToPoint[MAXN],n,nowTime;
    using SegmentTree::SegmentTree;

    SegmentTree stree;

    void getInfo(int now,int father) {
        fathers[now] = father;
        depths[now] = depths[father] + 1;
        sizes[now] = 1;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.to == father) continue;
            values[tmpEdge.to] = tmpEdge.weight;
            edgesToPoint[tmpEdge.sign] = tmpEdge.to;
            getInfo(tmpEdge.to,now);
            if(sons[now] == 0 || sizes[sons[now]] < sizes[tmpEdge.to]) {
                sons[now] = tmpEdge.to;
            }
            sizes[now] += sizes[tmpEdge.to];
        }
    }

    void mapIndex(int now,int father,int anc) {
        mapedIndexs[now] = ++nowTime;
        tops[now] = anc;
        if(sons[now] != 0) {
            mapIndex(sons[now],now,anc);
        }
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.to == father || tmpEdge.to == sons[now]) continue;
            mapIndex(tmpEdge.to,now,tmpEdge.to);
        }
    }

    void build() {
        getInfo(1,0);
        mapIndex(1,0,1);
        for(int i = 1;i <= n;i++) {
            mapedValues[mapedIndexs[i]] = values[i];
        }
        stree = SegmentTree(1,nowTime,mapedValues);
    }

    void init(int n) {
        Tree::n = n;
        for(int i = 0;i < n - 1;i++) {
            int u = read<int>(),v = read<int>(),w = read<int>();
            graph.addEdge(u,v,w,i + 1);
            graph.addEdge(v,u,w,i + 1);
        }
        build();
    }

    void change(int sign,int value) {
        sign = edgesToPoint[sign];
        stree.makeSame(mapedIndexs[sign],mapedIndexs[sign],value);
    }

    void makeSame(int u,int v,int value) {
        while(tops[u] != tops[v]) {
            if(depths[tops[u]] < depths[tops[v]]) {
                swap(u,v);
            }
            stree.makeSame(mapedIndexs[tops[u]],mapedIndexs[u],value);
            u = fathers[tops[u]];
        }
        if(u == v) return;
        if(depths[u] < depths[v]) {
            swap(u,v);
        }
        stree.makeSame(mapedIndexs[sons[v]],mapedIndexs[u],value);
    }

    void addVal(int u,int v,int value) {
        while(tops[u] != tops[v]) {
            if(depths[tops[u]] < depths[tops[v]]) {
                swap(u,v);
            }
            stree.addVal(mapedIndexs[tops[u]],mapedIndexs[u],value);
            u = fathers[tops[u]];
        }
        if(u == v) return;
        if(depths[u] < depths[v]) {
            swap(u,v);
        }
        stree.addVal(mapedIndexs[sons[v]],mapedIndexs[u],value);
    }

    int getMax(int u,int v) {
        int result = 0;
        while(tops[u] != tops[v]) {
            if(depths[tops[u]] < depths[tops[v]]) {
                swap(u,v);
            }
            result = max(result,stree.getMax(mapedIndexs[tops[u]],mapedIndexs[u]));
            u = fathers[tops[u]];
        }
        if(u == v) return result;
        if(depths[u] < depths[v]) {
            swap(u,v);
        }
        result = max(result,stree.getMax(mapedIndexs[sons[v]],mapedIndexs[u]));
        return result;
    }
}

using namespace Tree;

int main() {
    int n = read<int>();
    Tree::init(n);
    char *buffer = new char[7];
    while(true) {
        scanf("%s",buffer);
        if(buffer[0] == 'C') {
            if(buffer[1] == 'h') {
                int k = read<int>(),w = read<int>();
                change(k,w);
            }else {
                int u = read<int>(),v = read<int>(),w = read<int>();
                makeSame(u,v,w);
            }
        }else if(buffer[0] == 'A') {
            int u = read<int>(),v = read<int>(),w = read<int>();
            addVal(u,v,w);
        }else if(buffer[0] == 'M') {
            int u = read<int>(),v = read<int>();
            printf("%d\n",getMax(u,v));
        }else if(buffer[0] == 'S') {
            break;
        }
    }
    return 0;
}
