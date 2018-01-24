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

    ~Graph() {
        delete[] edges;
        delete[] heads;
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
        updateInfo(now);
    }

    int getValue(int left,int right) {
        return getValue(root,left,right);
    }

    int getValue(Node *now,int left,int right) {
        if(now->left == left && now->right == right) {
            return now->value;
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return getValue(now->ch[0],left,right);
            }else {
                return min(getValue(now->ch[0],left,mid),getValue(now->ch[1],mid + 1,right));
            }
        }else {
            return getValue(now->ch[1],left,right);
        }
    }

    ~SegmentTree() {
        if(root != NULL) {
            delete root;
        }
    }
};

struct Tree {
    int *sizes,*tops,*ends,*fathers,*heavySons,*reIndexs,*depths;
    SegmentTree *upTree,*downTree;
    Graph *graph;

    Tree(Graph *graph) : graph(graph) {
        int size = graph->nodeSize;
        sizes = new int[size];
        tops = new int[size];
        ends = new int[size];
        fathers = new int[size];
        heavySons = new int[size];
        reIndexs = new int[size];
        depths = new int[size];
        depths[0] = 0;
        getTreeInfo(0,-1);
        int nowIndex = 0;
        mapIndex(0,-1,0,nowIndex);
        upTree = new SegmentTree(size);
        downTree = new SegmentTree(size);
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
            ends[now] = ends[heavySons[now]];
        }else {
            ends[now] = now;
        }
        for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
            Graph::Edge &tmpEdge = graph->edges[i];
            if(tmpEdge.to == father || tmpEdge.to == heavySons[now]) continue;
            mapIndex(tmpEdge.to,now,tmpEdge.to,nowIndex);
        }
    }

    void makeRed(int pos) {
        int u = pos;
        while(u != -1) {
            int topU = tops[u];
            upTree->updateValue(reIndexs[u],depths[pos] - depths[topU]);
            downTree->updateValue(reIndexs[u],depths[pos] - depths[u] + depths[ends[u]] - depths[u]);
            u = fathers[topU];
        }
    }

    int getMinDis(int pos) {
        int u = pos,result = INF;
        while(u != -1) {
            int topU = tops[u],endU = ends[u];
            result = min(result,downTree->getValue(reIndexs[topU],reIndexs[u]) + depths[pos] - depths[u] - (depths[endU] - depths[u]));
            result = min(result,upTree->getValue(reIndexs[u],reIndexs[endU]) + depths[pos] - depths[u] - (depths[u] - depths[topU]));
            u = fathers[topU];
        }
        return result;
    }

    ~Tree() {
        delete[] sizes;
        delete[] tops;
        delete[] ends;
        delete[] fathers;
        delete[] heavySons;
        delete[] reIndexs;
        delete[] depths;
        delete upTree;
        delete downTree;
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    Graph *graph = new Graph((n - 1) * 2,n);
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph->addEdge(u,v);
        graph->addEdge(v,u);
    }
    Tree tree(graph);
    tree.makeRed(0);
    while(m--) {
        int opt = read<int>(),v = read<int>();
        v--;
        if(opt == 1) {
            tree.makeRed(v);
        }else {
            printf("%d\n",tree.getMinDis(v));
        }
    }
    delete graph;
    return 0;
}
