#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <utility>
#include <cmath>

using namespace std;

const int MAX_DEPTH = 18;
const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c  < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

/*
struct SegmentNode {
    int ch[2],cnt;

    SegmentNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    SegmentNode(int lc,int rc,int cnt) : cnt(cnt) {
        ch[0] = lc;
        ch[1] = rc;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int tmp[QUERY_TMP_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root,left,right;

    static int newNode() {
        sn[++segmentSize] = SegmentNode();
        return segmentSize;
    }

    static int newNode(int nodeSign) {
        sn[++segmentSize] = SegmentNode(sn[nodeSign].ch[0],sn[nodeSign].ch[1],sn[nodeSign].cnt);
        return segmentSize;
    }

    SegmentTree() : root(0) , left(0) , right(0) { }

    SegmentTree(int left,int right) : left(left) , right(right) {
        root = newNode();
    }

    SegmentTree(int root,int left,int right) : root(root) , left(left) , right(right) { }

    void updateInfo(int now) {
        sn[now].cnt = sn[sn[now].ch[0]].cnt + sn[sn[now].ch[1]].cnt;
    }

    void update(int pos,int val) {
        update(root,left,right,pos,val);
    }

    void update(int now,int nowLeft,int nowRight,int pos,int val) {
        if(nowLeft == nowRight) {
            sn[now].cnt += val;
            return;
        }
        int mid = (nowLeft + nowRight) >> 1;
        if(pos <= mid) {
            if(sn[now].ch[0] == 0) {
                sn[now].ch[0] = newNode();
            }else {
                sn[now].ch[0] = newNode(sn[now].ch[0]);
            }
            update(sn[now].ch[0],nowLeft,mid,pos,val);
        }else {
            if(sn[now].ch[1] == 0) {
                sn[now].ch[1] = newNode();
            }else {
                sn[now].ch[1] = newNode(sn[now].ch[1]);
            }
            update(sn[now].ch[1],mid + 1,nowRight,pos,val);
        }
        updateInfo(now);
    }

    static int queryKth(SegmentTree u,SegmentTree v,SegmentTree lca,SegmentTree lcaFa,int k) {
        tmp[0] = u.root;
        tmp[1] = v.root;
        tmp[2] = lca.root;
        tmp[3] = lcaFa.root;
        return queryKth(u.left,u.right,k);
    }

    static int queryKth(int nowLeft,int nowRight,int k) {
        if(nowLeft == nowRight) {
            return nowLeft;
        }
        int cnt = sn[sn[tmp[0]].ch[0]].cnt + sn[sn[tmp[1]].ch[0]].cnt - sn[sn[tmp[2]].ch[0]].cnt - sn[sn[tmp[3]].ch[0]].cnt;
        //printf("Ask range %d,%d,%d\n,first %d,second %d,third %d,forth %d,ans %d\n",left,(left + right) >> 1,right,sn[sn[tmp[0]].ch[0]].cnt,sn[sn[tmp[1]].ch[0]].cnt,sn[sn[tmp[2]].ch[0]].cnt,sn[sn[tmp[3]].ch[0]].cnt,cnt);
        int mid = (nowLeft + nowRight) >> 1;
        if(cnt < k) {
            for(int i = 0;i < 4;i++) {
                tmp[i] = sn[tmp[i]].ch[1];
            }
            return queryKth(mid + 1,nowRight,k - cnt);
        }else {
            for(int i = 0;i < 4;i++) {
                tmp[i] = sn[tmp[i]].ch[0];
            }
            return queryKth(nowLeft,mid,k);
        }
    }

    SegmentTree copy() {
        return SegmentTree(newNode(root),left,right);
    }

} strees[MAXN];
*/

struct SegmentTree {
    struct Node {
        Node *leftChild,*rightChild;
        int left,right,cnt;

        Node(int left,int right) : left(left) , right(right) , cnt(0) {
            leftChild = NULL;
            rightChild = NULL;
        }

        Node(Node *lc,Node *rc,int left,int right,int cnt) : leftChild(lc) , rightChild(rc) , left(left) , right(right) ,cnt(cnt) { }

        Node *copy() {
            return new Node(leftChild,rightChild,left,right,cnt);
        }
    };

    Node *root;

    SegmentTree(int left,int right) {
        root = new Node(left,right);
    }

    SegmentTree(Node *root) : root(root) { }

    SegmentTree *copy() {
        return new SegmentTree(root->copy());
    }

    static int getCnt(Node *now) {
        if(now == NULL) return 0;
        return now->cnt;
    }

    static int getLeftChildCnt(Node *now) {
        if(now == NULL) return 0;
        return getCnt(now->leftChild);
    }

    static Node *getLeftChild(Node *now) {
        if(now == NULL) return NULL;
        return now->leftChild;
    }

    static Node *getRightChild(Node *now) {
        if(now == NULL) return NULL;
        return now->rightChild;
    }

    static int queryKth(SegmentTree *u,SegmentTree *v,SegmentTree *lca,SegmentTree *lcaFa,int k) {
        return queryKth(u->root->left,u->root->right,u->root,v->root,lca->root,lcaFa->root,k);
    }

    static int queryKth(int nowLeft,int nowRight,Node *nowU,Node *nowV,Node *nowLCA,Node *nowLCAFa,int k) {
        if(nowLeft == nowRight) {
            return nowLeft;
        }
        int mid = (nowLeft + nowRight) >> 1;
        int cnt = getLeftChildCnt(nowU) + getLeftChildCnt(nowV) - getLeftChildCnt(nowLCA) - getLeftChildCnt(nowLCAFa);
        if(cnt < k) {
            return queryKth(mid + 1,nowRight,getRightChild(nowU),getRightChild(nowV),getRightChild(nowLCA),getRightChild(nowLCAFa),k - cnt);
        }else {
            return queryKth(nowLeft,mid,getLeftChild(nowU),getLeftChild(nowV),getLeftChild(nowLCA) , getLeftChild(nowLCAFa),k);
        }
    }

    void update(int pos) {
        update(root,pos);
    }

    void update(Node *now,int pos) {
        now->cnt++;
        if(now->left == now->right) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            if(now->leftChild == NULL) {
                now->leftChild = new Node(now->left,mid);
            }else {
                now->leftChild = now->leftChild->copy();
            }
            update(now->leftChild,pos);
        }else {
            if(now->rightChild == NULL) {
                now->rightChild = new Node(mid + 1,now->right);
            }else {
                now->rightChild = now->rightChild->copy();
            }
            update(now->rightChild,pos);
        }
    }


};

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
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

};

/*
构建father
构建主席树
*/
void dfs(int now,int father,int *values,int *depths,int **fathers,SegmentTree **strees,Graph &graph) {
    depths[now] = depths[father] + 1;
    strees[now] = strees[father]->copy();
    strees[now]->update(values[now]);
    fathers[now][0] = father;
    for(int i = graph.heads[now];i != - 1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now,values,depths,fathers,strees,graph);
    }
}

void init(int N,int **fathers) {
    for(int i = 1;i <= MAX_DEPTH;i++) {
        for(int j = 1;j <= N;j++) {
            fathers[j][i] = fathers[fathers[j][i - 1]][i - 1];
        }
    }
}

int LCA(int u,int v,int **fathers,int *depths) {
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            u = fathers[u][i];
        }
    }
    if(u == v) {
        return u;
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            u = fathers[u][i];
            v = fathers[v][i];
        }
    }
    return fathers[u][0];
}

int main() {
    int N = read<int>(),M = read<int>(),*values = new int[N + 1],*sortedValues = new int[N],*sign = new int[N + 1],*depths = new int[N + 1],**fathers = new int*[N + 1];
    depths[0] = 0;
    values[0] = 0;
    Graph graph((N - 1) * 2,N + 1);
    for(int i = 0;i <= N;i++) {
        fathers[i] = new int[MAX_DEPTH + 1];
        memset(fathers[i],0,sizeof(int) * (MAX_DEPTH + 1));
    }
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
        sortedValues[i - 1] = values[i];
    }
    sort(sortedValues,sortedValues + N);
    int sortSize = unique(sortedValues,sortedValues + N) - sortedValues;
    for(int i = 1;i <= N;i++) {
        int newSign = lower_bound(sortedValues,sortedValues + sortSize,values[i]) - sortedValues;
        sign[newSign] = values[i];
        values[i] = newSign;
    }
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    SegmentTree **strees = new SegmentTree*[N + 1];
    strees[0] = new SegmentTree(0,N - 1);
    dfs(1,0,values,depths,fathers,strees,graph);
    init(N,fathers);
    int lastAns = 0;
    while(M--) {
        int u = read<int>(),v = read<int>(),k = read<int>();
        u ^= lastAns;
        int lca = LCA(u,v,fathers,depths);
        lastAns = sign[SegmentTree::queryKth(strees[u],strees[v],strees[lca],strees[fathers[lca][0]],k)];
        printf("%d",lastAns);
        if(M != 0) printf("\n");
    }
    return 0;
}
