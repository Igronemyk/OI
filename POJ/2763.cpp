#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;
const int BUFFER_SIZE = 7;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,w,sign;
    };
    Edge *edges;
    int tot,*heads,nodeSize;

    Graph(int edgeSize,int nodeSize) : nodeSize(nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v,int w,int sign) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        edges[tot].w = w;
        edges[tot].sign = sign;
        heads[u] = tot++;
    }

    ~Graph() {
        delete[] edges;
        delete[] heads;
    }
};

struct SegmentTree {
    struct Node {
        int left,right,sum;
        Node *ch[2];

        Node(int left,int right) : left(left) , right(right) , sum(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }

        bool isLeafNode() {
            return left == right;
        }

        ~Node() {
            if(ch[0] != NULL) {
                delete ch[0];
            }
            if(ch[1] != NULL) {
                delete ch[1];
            }
        }

    };

    Node *root;

    SegmentTree(int size,int *values) {
        root = new Node(0,size - 1);
        build(root,values);
    }

    void updateInfo(Node *now) {
        now->sum = now->ch[0]->sum + now->ch[1]->sum;
    }

    void build(Node *now,int *values) {
        if(now->isLeafNode()) {
            now->sum = values[now->left];
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->ch[0] = new Node(now->left,mid);
        build(now->ch[0],values);
        now->ch[1] = new Node(mid + 1,now->right);
        build(now->ch[1],values);
        updateInfo(now);
    }

    void changeValue(int pos,int val) {
        changeValue(root,pos,val);
    }

    void changeValue(Node *now,int pos,int val) {
        if(now->left == pos && now->right == pos) {
            now->sum = val;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            changeValue(now->ch[0],pos,val);
        }else {
            changeValue(now->ch[1],pos,val);
        }
        updateInfo(now);
    }

    int getSum(int left,int right) {
        return getSum(root,left,right);
    }

    int getSum(Node *now,int left,int right) {
        if(now->left == left && now->right == right) {
            return now->sum;
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return getSum(now->ch[0],left,right);
            }else {
                return getSum(now->ch[0],left,mid) + getSum(now->ch[1],mid + 1,right);
            }
        }else {
            return getSum(now->ch[1],left,right);
        }
    }

    ~SegmentTree() {
        if(root != NULL) {
            delete root;
        }
    }

};

struct Tree {
    int *sizes,*fathers,*tops,*depth,*heavySons,*reIndexs,*heavySonsValues,*edgeToPoints;
    SegmentTree *stree;
    Graph *graph;

    Tree(Graph *graph) : graph(graph) {
        build();
    }

    void build() {
        int size = graph->nodeSize;
        sizes = new int[size];
        fathers = new int[size];
        tops = new int[size];
        depth = new int[size];
        heavySons = new int[size];
        reIndexs = new int[size];
        heavySonsValues = new int[size];
        edgeToPoints = new int[size];
        depth[0] = 0;
        getTreeInfo(0,-1);
        int *values = new int[size];
        int nowIndex = 0;
        mapIndex(0,-1,0,0,values,nowIndex);
        stree = new SegmentTree(size,values);
    }

    void getTreeInfo(int now,int father) {
        sizes[now] = 1;
        fathers[now] = father;
        if(father != -1) depth[now] = depth[father] + 1;
        int heavySon = -1,heavySonsValue = -1;
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == father) continue;
            getTreeInfo(tmpEdge.to,now);
            sizes[now] += sizes[tmpEdge.to];
            edgeToPoints[tmpEdge.sign] = tmpEdge.to;
            if(heavySon == -1 || sizes[heavySon] < sizes[tmpEdge.to]) {
                heavySon = tmpEdge.to;
                heavySonsValue = tmpEdge.w;
            }
        }
        heavySons[now] = heavySon;
        heavySonsValues[now] = heavySonsValue;
    }

    void mapIndex(int now,int father,int edgeValue,int anc,int *values,int &nowIndex) {
        tops[now] = anc;
        reIndexs[now] = nowIndex;
        values[nowIndex++] = edgeValue;
        if(heavySons[now] != -1) {
            mapIndex(heavySons[now],now,heavySonsValues[now],anc,values,nowIndex);
        }
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == father || tmpEdge.to == heavySons[now]) continue;
            mapIndex(tmpEdge.to,now,tmpEdge.w,tmpEdge.to,values,nowIndex);
        }
    }

    void changeValue(int pos,int val) {
        int u = edgeToPoints[pos];
        stree->changeValue(reIndexs[u],val);
    }

    int getSum(int u,int v) {
        int topU = tops[u],topV = tops[v],result = 0;
        while(topU != topV) {
            if(depth[topU] < depth[topV]) {
                swap(u,v);
                swap(topU,topV);
            }
            result += stree->getSum(reIndexs[topU],reIndexs[u]);
            u = fathers[topU];
            topU = tops[u];
        }
        if(u == v) return result;
        if(depth[u] < depth[v]) {
            swap(u,v);
        }
        result += stree->getSum(reIndexs[heavySons[v]],reIndexs[u]);
        return result;
    }

    ~Tree() {
        delete[] sizes;
        delete[] fathers;
        delete[] tops;
        delete[] depth;
        delete[] heavySons;
        delete[] reIndexs;
        delete[] heavySonsValues;
        delete[] edgeToPoints;
        delete stree;
    }
};

int main() {
    int n = read<int>(),q = read<int>(),s = read<int>();
    s--;
    Graph *graph = new Graph((n - 1) * 2,n);
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        u--; v--;
        graph->addEdge(u,v,w,i);
        graph->addEdge(v,u,w,i);
    }
    Tree tree(graph);
    while(q--) {
        int opt = read<int>();
        if(opt == 0) {
            int u = read<int>();
            u--;
            printf("%d\n",tree.getSum(s,u));
            s = u;
        }else {
            int i = read<int>(),w = read<int>();
            i--;
            tree.changeValue(i,w);
        }
    }
    delete graph;
    return 0;
}
