#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 5e5;
const int MAXN = 5e5;
const long long INF = 0x3f3f3f3f3f3f3f3f;

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
    Edge edges[MAXN * 5];

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

struct SegmentNode {
    int ch[2];
    int sign;

    SegmentNode() : sign(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    SegmentNode(int sign) : sign(sign) {
        ch[0] = 0;
        ch[1] = 0;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;
//leftTree use rightLink rightTree use leftLink
struct SegmentTree {
    int root,left,right;

    static int newNode() {
        ++segmentSize;
        sn[segmentSize] = SegmentNode(segmentSize);
        return segmentSize;
    }

    SegmentTree(int n,bool isLeftLink) : left(1) , right(n) {
        root = newNode();
        build(root,left,right,isLeftLink);
    }

    void build(int now,int left,int right,bool isLeftLink) {
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(left == mid) {
            sn[now].ch[0] = left;
        }else {
            sn[now].ch[0] = newNode();
            build(sn[now].ch[0],left,mid,isLeftLink);
        }
        if(isLeftLink) {
            graph.addEdge(now,sn[now].ch[0],0);
        }else {
            graph.addEdge(sn[now].ch[0],now,0);
        }
        if(mid + 1 == right) {
            sn[now].ch[1] = right;
        }else {
            sn[now].ch[1] = newNode();
            build(sn[now].ch[1],mid + 1,right,isLeftLink);
        }
        if(isLeftLink) {
            graph.addEdge(now,sn[now].ch[1],0);
        }else {
            graph.addEdge(sn[now].ch[1],now,0);
        }
    }

    void link(int l,int r,int sign,int weight,bool isLeftLink) {
        link(root,left,right,l,r,sign,weight,isLeftLink);
    }

    void link(int now,int left,int right,int l,int r,int sign,int weight,bool isLeftLink) {
        if(left == l && right == r) {
            if(isLeftLink) {
                graph.addEdge(now,sign,weight);
            }else {
                graph.addEdge(sign,now,weight);
            }
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                link(sn[now].ch[0],left,mid,l,r,sign,weight,isLeftLink);
            }else {
                link(sn[now].ch[0],left,mid,l,mid,sign,weight,isLeftLink);
                link(sn[now].ch[1],mid + 1,right,mid + 1,r,sign,weight,isLeftLink);
            }
        }else {
            link(sn[now].ch[1],mid + 1,right,l,r,sign,weight,isLeftLink);
        }
    }

    static void init(int n) {
        for(int i = 1;i <= n;i++) {
            newNode();
        }
    }
};

bool vis[MAXN];
long long dis[MAXN];

void spfa(int start) {
    memset(vis,false,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    queue<int> que;
    que.push(start);
    dis[start] = 0;
    vis[start] = true;
    while(!que.empty()) {
        int tmp = que.front();
        que.pop();
        vis[tmp] = false;
        for(int i = graph.heads[tmp];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(dis[tmp] + tmpEdge.weight < dis[tmpEdge.to]) {
                dis[tmpEdge.to] = dis[tmp] + tmpEdge.weight;
                if(!vis[tmpEdge.to]) {
                    vis[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
}

int main() {
    int n = read<int>(),q = read<int>(),s = read<int>();
    SegmentTree::init(n);
    SegmentTree leftTree(n,true),rightTree(n,false);
    while(q--) {
        int t = read<int>();
        switch(t) {
            case 1: {
                int v = read<int>(),u = read<int>(),w = read<int>();
                graph.addEdge(v,u,w);
                break;
            }
            case 2: {
                int v = read<int>(),l = read<int>(),r = read<int>(),w = read<int>();
                leftTree.link(l,r,v,w,false);
                break;
            }
            case 3: {
                int v = read<int>(),l = read<int>(),r = read<int>(),w = read<int>();
                rightTree.link(l,r,v,w,true);
                break;
            }
        }
    }
    spfa(s);
    for(int i = 1;i <= n;i++) {
        printf("%lld ",(dis[i] == INF ? -1 : dis[i]));
    }
    printf("\n");
    return 0;
}
