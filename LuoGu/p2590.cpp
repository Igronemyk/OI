#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const char *OPT_CHANGE = "CHANGE";
const char *OPT_QMAX = "QMAX";
const char *OPT_QSUM = "QSUM";
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
        int left,right,value,maxValue,lazyTag;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , value(-1) , maxValue(-1) , lazyTag(-1) { }
        Node(int left,int right) : left(left) , right(right) , value(0) , maxValue(0) , lazyTag(0) , leftChild(NULL) , rightChild(NULL) { }

        bool isLeafNode() {
            return left == right;
        }

        bool hasLazyTag() {
            return lazyTag != 0;
        }

    };

    Node *root;

    SegmentTree() {
        root = NULL;
    }

    SegmentTree(int *values,int size) {
        root = new Node(0,size - 1);
        build(values,root);
    }

    void build(int *values,Node *now) {
        if(now->isLeafNode()) {
            now->value = values[now->left];
            now->maxValue = values[now->left];
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
        add(left,right,value,root);
    }

    void add(int left,int right,int value,Node *now) {
        if(now->left == left && now->right == right) {
            now->value += (now->right - now->left + 1) * value;
            now->maxValue += value;
            if(!now->isLeafNode()) {
                now->lazyTag += value;
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
                return query(left,mid,now->leftChild) + query(mid + 1,right,now->rightChild);
            }
        }
    }

    int queryMax(int left,int right) {
        return queryMax(left,right,root);
    }

    int queryMax(int left,int right,Node *now) {
        if(now->left == left && now->right == right) {
            return now->maxValue;
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            return queryMax(left,right,now->leftChild);
        }else {
            if(left > mid) {
                return queryMax(left,right,now->rightChild);
            }else {
                return max(queryMax(left,mid,now->leftChild),queryMax(mid + 1,right,now->rightChild));
            }
        }
    }


    void pushDown(Node *now) {
        updateTag(now->lazyTag,now->leftChild);
        updateTag(now->lazyTag,now->rightChild);
        now->lazyTag = 0;
    }

    void updateTag(int lazyTag,Node *now) {
        now->value += (now->right - now->left + 1) * lazyTag;
        if(!now->isLeafNode()) {
            now->lazyTag += lazyTag;
        }
    }

    void updateInfo(Node *now) {
        now->value = now->leftChild->value + now->rightChild->value;
        now->maxValue = max(now->leftChild->maxValue,now->rightChild->maxValue);
    }

};

struct Tree {
    Graph graph;
    SegmentTree values;
    int nodeSize,*size,*depth,*fathers,*heavySon,*mapedIndex,*top;
    Tree(Graph &graph,int nodeSize,int *nodeWeight,int root) : graph(graph) , nodeSize(nodeSize) {
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
        values = SegmentTree(reValue,nodeSize);
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
            result += values.query(mapedIndex[topU],mapedIndex[u]);
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        result += values.query(mapedIndex[v],mapedIndex[u]);
        return result;
    }

    int getMaxVal(int u,int v) {
        int topU = top[u],topV = top[v],result = -INF;
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            result = max(result,values.queryMax(mapedIndex[topU],mapedIndex[u]));
            u = fathers[topU];
            topU = top[u];
        }
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        result = max(result,values.queryMax(mapedIndex[v],mapedIndex[u]));
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
    int n = read<int>();
    Graph graph((n - 1) * 2,n);
    for(int i = 0;i < n - 1;i++) {
        int a = read<int>(),b = read<int>();
        a--; b--;
        graph.addEdge(a,b);
        graph.addEdge(b,a);
    }
    int *initWeight = new int[n];
    for(int i = 0;i < n;i++) {
        initWeight[i] = read<int>();
    }
    Tree tree(graph,n,initWeight,0);
    int q = read<int>();
    char *tmpOpt = new char[8];
    while(q--) {
        scanf("%s",tmpOpt);
        if(strcmp(tmpOpt,OPT_CHANGE) == 0) {
            int u =read<int>(),t = read<int>();
            u--;
            int oldVal = tree.getVal(u,u);
            tree.addVal(u,u,t - oldVal);
        }else if(strcmp(tmpOpt,OPT_QMAX) == 0) {
            int u = read<int>(),v = read<int>();
            u--; v--;
            printf("%d\n",tree.getMaxVal(u,v));
        }else if(strcmp(tmpOpt,OPT_QSUM) == 0) {
            int u = read<int>(),v = read<int>();
            u--; v--;
            printf("%d\n",tree.getVal(u,v));
        }
    }
    return 0;
}
