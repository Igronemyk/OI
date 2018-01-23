#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int BUFFER_SIZE = 10;

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
    Edge *edges;
    int tot,*heads,edgeSize,nodeSize;

    Graph() : edges(NULL) , tot(-1) , heads(NULL) , edgeSize(-1) , nodeSize(-1) { }

    Graph(int edgeSize,int nodeSize) : edgeSize(edgeSize) , nodeSize(nodeSize) {
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
        int left,right,sum,tag;
        Node *leftChild,*rightChild;

        Node(int left,int right) : left(left) , right(right) , sum(0) , tag(-1) , leftChild(NULL) , rightChild(NULL) { }

        bool isLeafNode() {
            return left == right;
        }

        bool hasLazyTag() {
            return tag != -1;
        }
    };

    Node *root;

    SegmentTree(int size) {
        root = new Node(0,size - 1);
        build(root);
    }

    void build(Node *now) {
        if(now->isLeafNode()) return;
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild);
        updateInfo(now);
    }

    void pushDown(Node *now) {
        if(!now->hasLazyTag()) return;
        updateTag(now->leftChild,now->tag);
        updateTag(now->rightChild,now->tag);
        now->tag = -1;
    }

    void updateTag(Node *now,int tag) {
        if(!now->isLeafNode()) now->tag = tag;
        if(tag == 0) {
            now->sum = 0;
        }else {
            now->sum = now->right - now->left + 1;
        }
    }

    int querySum(int left,int right) {
        return querySum(root,left,right);
    }

    int querySum(Node *now,int left,int right) {
        if(now->left == left && now->right == right) {
            return now->sum;
        }
        pushDown(now);
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return querySum(now->leftChild,left,right);
            }else {
                return querySum(now->leftChild,left,mid) + querySum(now->rightChild,mid + 1,right);
            }
        }else {
            return querySum(now->rightChild,left,right);
        }
    }

    void makeSame(int left,int right,int tag) {
        makeSame(root,left,right,tag);
    }

    void makeSame(Node *now,int left,int right,int tag) {
        if(now->left == left && now->right == right) {
            updateTag(now,tag);
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                makeSame(now->leftChild,left,right,tag);
            }else {
                makeSame(now->leftChild,left,mid,tag);
                makeSame(now->rightChild,mid + 1,right,tag);
            }
        }else {
            makeSame(now->rightChild,left,right,tag);
        }
        updateInfo(now);
    }

    void updateInfo(Node *now) {
        now->sum = now->leftChild->sum + now->rightChild->sum;
    }
};

struct Tree {
    Graph *graph;
    int *sizes,*heavySons,*reIndexs,*top,*fathers,*depth;
    SegmentTree *stree;

    Tree(Graph *graph) {
        this->graph = graph;
        build();
    }

    void build() {
        sizes = new int[graph->nodeSize];
        heavySons = new int[graph->nodeSize];
        reIndexs = new int[graph->nodeSize];
        top = new int[graph->nodeSize];
        fathers = new int[graph->nodeSize];
        depth = new int[graph->nodeSize];
        stree = new SegmentTree(graph->nodeSize);
        depth[0] = 0;
        getTreeInfo(0,-1);
        int nowIndex = 0;
        mapIndex(0,-1,0,nowIndex);
    }

    void getTreeInfo(int now,int father) {
        int size = 1,heavySon = -1;
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            getTreeInfo(tmpEdge.to,now);
            size += sizes[tmpEdge.to];
            if(heavySon == -1 || sizes[heavySon] < sizes[tmpEdge.to]) {
                heavySon = tmpEdge.to;
            }
        }
        if(father != -1) depth[now] = depth[father] + 1;
        fathers[now] = father;
        sizes[now] = size;
        heavySons[now] = heavySon;
    }

    void mapIndex(int now,int father,int anc,int &nowIndex) {
        top[now] = anc;
        reIndexs[now] = nowIndex++;
        if(heavySons[now] != -1) {
            mapIndex(heavySons[now],now,anc,nowIndex);
        }
        for(int i = graph->heads[now];i != - 1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == heavySons[now]) continue;
            mapIndex(tmpEdge.to,now,tmpEdge.to,nowIndex);
        }
    }

    int getValue(int u,int v) {
        int topU = top[u],topV = top[v],result = 0;
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            result += stree->querySum(reIndexs[topU],reIndexs[u]);
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        result += stree->querySum(reIndexs[v],reIndexs[u]);
        return result;
    }

    void makeSame(int u,int v,int tag) {
        int topU = top[u],topV = top[v];
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            stree->makeSame(reIndexs[topU],reIndexs[u],tag);
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        stree->makeSame(reIndexs[v],reIndexs[u],tag);
    }

    int getChildsValue(int pos) {
        return stree->querySum(reIndexs[pos],reIndexs[pos] + sizes[pos] - 1);
    }

    void makeChildsSame(int pos,int tag) {
        stree->makeSame(reIndexs[pos],reIndexs[pos] + sizes[pos] - 1,tag);
    }
};

int main() {
    int n = read<int>();
    Graph *graph = new Graph(n - 1,n);
    for(int i = 1;i < n;i++) {
        int father = read<int>();
        graph->addEdge(father,i);
    }
    Tree tree(graph);
    char *buffer = new char[BUFFER_SIZE];
    int q = read<int>();
    while(q--) {
        scanf("%s",buffer);
        int pos = read<int>();
        if(buffer[0] == 'i') {
            int oldValue = tree.getValue(0,pos);
            tree.makeSame(0,pos,1);
            printf("%d\n",tree.getValue(0,pos) - oldValue);
        }else {
            int oldValue = tree.getChildsValue(pos);
            tree.makeChildsSame(pos,0);
            printf("%d\n",oldValue);
        }
    }
    return 0;
}

