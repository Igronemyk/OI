#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads,nodeSize;

    Graph(int edgeSize,int nodeSize) : nodeSize(nodeSize) {
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
};

struct SegmentTree {
    struct Node {
        int left,right,value;
        Node *ch[2];

        Node(int left,int right) : left(left) , right(right) , value(INF) {
            ch[0] = NULL;
            ch[1] = NULL;
        }

        bool isLeafNode() {
            return left == right;
        }
    };

    Node *root;

    SegmentTree(int size) {
        root = new Node(0,size - 1);
        build(root);
    }

    void updateInfo(Node *now) {
        now->value = min(now->ch[0]->value,now->ch[1]->value);
    }

    void build(Node *now) {
        if(now->isLeafNode()) return;
        int mid = (now->left + now->right) >> 1;
        now->ch[0] = new Node(now->left,mid);
        build(now->ch[0]);
        now->ch[1] = new Node(mid + 1,now->right);
        build(now->ch[1]);
        updateInfo(now);
    }

    void updateValue(int pos,int val) {
        updateValue(root,pos,val);
    }

    void updateValue(Node *now,int pos,int val) {
        if(now->isLeafNode()) {
            now->value = min(now->value,val);
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            updateValue(now->ch[0],pos,val);
        }else {
            updateValue(now->ch[1],pos,val);
        }
    }
};

struct Tree {
    int *sizes,*tops,*fathers,*heavySons,*reIndexs,*depths;
    SegmentTree *childTree,*otherTree;
    Graph *graph;

    Tree(Graph *graph) : graph(graph) {
        int size = graph->nodeSize;
        sizes = new int[size];
        tops = new int[size];
        fathers = new int[size];
        heavySons = new int[size];
        reIndexs = new int[size];
        depths = new int[size];
        depths[0] = 0;
        getTreeInfo(0,-1);
        int nowIndex = 0;
        mapIndex(0,-1,0,nowIndex);
        childTree = new SegmentTree(size);
        otherTree = new SegmentTree(size);
    }

    void getTreeInfo(int now,int father) {
        fathers[now] = father;
        sizes[now] = 1;
        if(father != -1) depths[now] = depths[father] + 1;
        int heavySon = -1;
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == father) continue;
            getTreeInfo(tmpEdge.to,now);
            sizes[now] += sizes[tmpEdge.to];
            if(heavySon == -1 || sizes[heavySon] < sizes[tmpEdge.to]) {
                heavySon = tmpEdge.to;
            }
        }
        heavySons[now] = heavySon;
    }

    void mapIndex(int now,int father,int anc,int &nowIndex) {
        tops[now] = anc;
        reIndexs[now] = nowIndex++;
        if(heavySons[now] != -1) {
            mapIndex(heavySons[now],now,anc,nowIndex);
        }
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == father || tmpEdge.to == heavySons[now]) continue;
            mapIndex(tmpEdge.to,now,tmpEdge.to,nowIndex);
        }
    }

    void makeRed(int pos) {
        childTree->updateValue(pos,0);

    }
};

int main() {
    return 0;
}
