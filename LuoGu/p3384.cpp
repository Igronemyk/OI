#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

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
    int tot,*heads;

    Graph() {
        edges = NULL;
        tot = -1;
        heads = NULL;
    }

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
};

struct SegmentTree {

    struct Node {
        int left,right,value,lazyTag;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , value(-1) , lazyTag(-1) { }
        Node(int left,int right) : left(left) , right(right) , value(0) , lazyTag(0) , leftChild(NULL) , rightChild(NULL) { }

        bool isLeafNode() {
            return left == right;
        }

        bool hasLazyTag() {
            return lazyTag != 0;
        }

    };

    Node *root;
    int modder;

    SegmentTree() {
        root = NULL;
        modder = -1;
    }

    SegmentTree(int *values,int size,int modder) : modder(modder) {
        root = new Node(0,size - 1);
        build(values,root);
    }

    void build(int *values,Node *now) {
        if(now->isLeafNode()) {
            now->value = values[now->left];
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(values,now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(values,now->rightChild);
        updateInfo(now);
    }

    void add(int left,int right,int value) {
        value %= modder;
        add(left,right,value,root);
    }

    void add(int left,int right,int value,Node *now) {
        if(now->left == left && now->right == right) {
            now->value = (now->value + ((now->right - now->left + 1) * 1LL * value) % modder) % modder;
            if(!now->isLeafNode()) {
                now->lazyTag = (now->lazyTag + value) % modder;
            }
            return;
        }
        if(now->hasLazyTag()) {
            pushDown(now);
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            add(left,right,value,now->leftChild);
        }else {
            if(left > mid) {
                add(left,right,value,now->rightChild);
            }else {
                add(left,mid,value,now->leftChild);
                add(mid + 1,right,value,now->rightChild);
            }
        }
        updateInfo(now);
    }

    int query(int left,int right) {
        return query(left,right,root);
    }

    int query(int left,int right,Node *now) {
        if(now->left == left && now->right == right) {
            return now->value;
        }
        if(now->hasLazyTag()) {
            pushDown(now);
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            return query(left,right,now->leftChild);
        }else {
            if(left > mid) {
                return query(left,right,now->rightChild);
            }else {
                return (query(left,mid,now->leftChild) + query(mid + 1,right,now->rightChild)) % modder;
            }
        }
    }

    void pushDown(Node *now) {
        updateTag(now->lazyTag,now->leftChild);
        updateTag(now->lazyTag,now->rightChild);
        now->lazyTag = 0;
    }

    void updateTag(int lazyTag,Node *now) {
        now->value = (now->value + ((now->right - now->left + 1) * 1LL * lazyTag) % modder) % modder;
        if(!now->isLeafNode()) {
            now->lazyTag = (now->lazyTag + lazyTag) % modder;
        }
    }

    void updateInfo(Node *now) {
        now->value = (now->leftChild->value + now->rightChild->value) % modder;
    }

};

struct Tree {
    Graph graph;
    SegmentTree values;
    int nodeSize,*size,*depth,*fathers,*heavySon,*mapedIndex,*top,modder;
    Tree(Graph &graph,int nodeSize,int *nodeWeight,int modder,int root) : graph(graph) , nodeSize(nodeSize) , modder(modder) {
        build(root,nodeWeight);
    }

    void build(int root,int *nodeWeight) {
        size = new int[nodeSize];
        depth = new int[nodeSize];
        heavySon = new int[nodeSize];
        fathers = new int[nodeSize];
        fathers[root] = -1;
        getTreeInfo(root,-1,0);
        mapedIndex = new int[nodeSize];
        top = new int[nodeSize];
        int nowIndex = 0;
        mapIndex(root,root,-1,nowIndex);
        int *reValue = new int[nodeSize];
        for(int i = 0;i < nodeSize;i++) {
            reValue[mapedIndex[i]] = nodeWeight[i];
        }
        values = SegmentTree(reValue,nodeSize,modder);
    }

    void getTreeInfo(int now,int father,int nowDepth) {
        size[now] = 1;
        fathers[now] = father;
        depth[now] = nowDepth;
        int nowHeavySon = -1;
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.to == father) continue;
            getTreeInfo(tmpEdge.to,now,nowDepth + 1);
            if(nowHeavySon == -1 || size[tmpEdge.to] > size[nowHeavySon]) nowHeavySon = tmpEdge.to;
            size[now] += size[tmpEdge.to];
        }
        heavySon[now] = nowHeavySon;
    }

    void mapIndex(int now,int ancestor,int father,int &nowIndex) {
        top[now] = ancestor;
        mapedIndex[now] = nowIndex++;
        if(heavySon[now] != -1) {
            mapIndex(heavySon[now],ancestor,now,nowIndex);
        }
        for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.to == father || tmpEdge.to == heavySon[now]) continue;
            mapIndex(tmpEdge.to,tmpEdge.to,now,nowIndex);
        }
    }

    void addVal(int u,int v,int val) {
        int topU = top[u],topV = top[v];
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            values.add(mapedIndex[topU],mapedIndex[u],val);
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        values.add(mapedIndex[v],mapedIndex[u],val);
    }

    int getVal(int u,int v) {
        int topU = top[u],topV = top[v],result = 0;
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            result = (result + values.query(mapedIndex[topU],mapedIndex[u])) % modder;
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        result = (result + values.query(mapedIndex[v],mapedIndex[u])) % modder;
        return result;
    }

    void addValToChilds(int pos,int val) {
        values.add(mapedIndex[pos],mapedIndex[pos] + size[pos] - 1,val);
    }

    int getChildsVal(int pos) {
        return values.query(mapedIndex[pos],mapedIndex[pos] + size[pos] - 1);
    }

};

int main() {
    int N = read<int>(),M = read<int>(),R = read<int>(),P = read<int>();
    int *initWeight = new int[N];
    for(int i = 0;i < N;i++) {
        initWeight[i] = read<int>();
    }
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int x = read<int>(),y = read<int>();
        x--; y--;
        graph.addEdge(x,y);
        graph.addEdge(y,x);
    }
    Tree tree(graph,N,initWeight,P,R - 1);
    while(M--) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int x = read<int>(),y = read<int>(),z = read<int>();
                x--; y--;
                tree.addVal(x,y,z);
                break;
            }
            case 2: {
                int x = read<int>(),y = read<int>();
                x--; y--;
                printf("%d\n",tree.getVal(x,y));
                break;
            }
            case 3: {
                int x = read<int>(),z = read<int>();
                x--;
                tree.addValToChilds(x,z);
                break;
            }
            case 4: {
                int x = read<int>();
                x--;
                printf("%d\n",tree.getChildsVal(x));
                break;
            }
        }
    }
    return 0;
}
