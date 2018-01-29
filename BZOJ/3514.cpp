#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 200000;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCT {
    struct Node {
        Node *father,*ch[2];
        int sign,minSign;
        bool rev;

        Node(int sign,int minSign) : father(NULL) , sign(sign) , minSign(minSign) , rev(false) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    } **nodes;


    int nodeSize;

    int getMinSign(int sign) {
        if(sign < nodeSize) {
            return INF;
        }else {
            return sign - nodeSize;
        }
    }

    LCT(int size,int nodeSize) : nodeSize(nodeSize) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) {
            nodes[i] = new Node(i,getMinSign(i));
        }
    }

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->ch[0] != now && now->father->ch[1] != now;
    }

    void updateInfo(Node *now) {
        now->minSign = getMinSign(now->sign);
        if(now->ch[0] != NULL && now->ch[0]->minSign < now->minSign) {
            now->minSign = now->ch[0]->minSign;
        }
        if(now->ch[1] != NULL && now->ch[1]->minSign < now->minSign) {
            now->minSign = now->ch[1]->minSign;
        }
    }

    void notifyAll(Node *now) {
        if(now == NULL) return;
        if(!isRoot(now)) notifyAll(now->father);
        pushDown(now);
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(!now->rev) return;
        updateReverseTag(now->ch[0]);
        updateReverseTag(now->ch[1]);
        swap(now->ch[0],now->ch[1]);
        updateReverseTag(now);
    }

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(!isRoot(father)) {
            anc->ch[anc->ch[1] == father] = now;
        }
        father->father = now;
        now->father = anc;
        int direction = father->ch[0] == now;
        father->ch[!direction] = now->ch[direction];
        now->ch[direction] = father;
        if(father->ch[!direction] != NULL) {
            father->ch[!direction]->father = father;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now) {
        if(now == NULL) return;
        notifyAll(now);
        while(!isRoot(now)) {
            Node *father = now->father,*anc = father->father;
            if(!isRoot(father)) {
                if((anc->ch[0] == father) ^ (father->ch[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void access(int pos) {
        Node *prev = NULL;
        for(Node *now = nodes[pos];now != NULL;now = now->father) {
            splay(now);
            now->ch[1] = prev;
            updateInfo(now);
            prev = now;
        }
    }

    void makeRoot(int pos) {
        Node *now = nodes[pos];
        access(pos);
        splay(now);
        updateReverseTag(now);
    }

    void split(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        makeRoot(u);
        access(v);
        splay(nodeV);
    }

    void link(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        makeRoot(u);
        nodeU->father = nodeV;
    }

    void cut(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        split(u,v);
        if(nodeV->ch[0] == nodeU) {
            nodeV->ch[0] = NULL;
            updateInfo(nodeV);
            nodeU->father = NULL;
        }
    }

    int getMinSign(int u,int v) {
        split(u,v);
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        return nodeV->minSign;
    }

    int getRoot(int pos) {
        Node *now = nodes[pos];
        access(pos);
        splay(now);
        while(now->ch[0] != NULL) {
            now = now->ch[0];
        }
        return now->sign;
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->ch[0]);
        printf("%d ",now->sign);
        print(now->ch[1]);
    }
};


struct SegmentTree {
    struct Node {
        Node *ch[2];
        int cnt;

        Node() : cnt(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }

        Node(Node *lc,Node *rc,int cnt) : cnt(cnt) {
            ch[0] = lc;
            ch[1] = rc;
        }

        Node *copy() {
            return new Node(ch[0],ch[1],cnt);
        }
    };

    Node *root;
    int left,right;

    SegmentTree(int left,int right) : left(left) , right(right) {
        root = new Node();
    }

    SegmentTree(Node *root,int left,int right) : root(root) , left(left) , right(right) { }

    void insert(int pos) {
        insert(root,left,right,pos);
    }

    void insert(Node *now,int left,int right,int pos) {
        now->cnt++;
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            if(now->ch[0] == NULL) {
                now->ch[0] = new Node();
            }else {
                now->ch[0] = now->ch[0]->copy();
            }
            insert(now->ch[0],left,mid,pos);
        }else {
            if(now->ch[1] == NULL) {
                now->ch[1] = new Node();
            }else {
                now->ch[1] = now->ch[1]->copy();
            }
            insert(now->ch[1],mid + 1,right,pos);
        }
    }

    SegmentTree *copy() {
        return new SegmentTree(root->copy(),left,right);
    }

    static int getCnt(Node *now) {
        if(now == NULL) return 0;
        return now->cnt;
    }

    static Node *getLeftChild(Node *now) {
        if(now == NULL) return NULL;
        return now->ch[0];
    }

    static Node *getRightChild(Node *now) {
        if(now == NULL) return NULL;
        return now->ch[1];
    }

    static int queryLessThan(SegmentTree *r,SegmentTree *l,int value) {
        return queryCnt(r->root,l->root,r->left,r->right,r->left,min(r->right,value - 1));
    }

    static int queryCnt(Node *r,Node *l,int nowLeft,int nowRight,int left,int right) {
        if(nowLeft == left && nowRight == right) {
            return getCnt(r) - getCnt(l);
        }
        int mid = (nowLeft + nowRight) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryCnt(getLeftChild(r),getLeftChild(l),nowLeft,mid,left,right);
            }else {
                return queryCnt(getLeftChild(r),getLeftChild(l),nowLeft,mid,left,mid) + queryCnt(getRightChild(r),getRightChild(l),mid + 1,nowRight,mid + 1,right);
            }
        }else{
            return queryCnt(getRightChild(r),getRightChild(l),mid + 1,nowRight,left,right);
        }
    }
};


typedef pair<int,int> Edge;

int main() {
    int N = read<int>(),M = read<int>(),K = read<int>(),type = read<int>();
    LCT lct(N + M,N);
    Edge *edges = new Edge[M];
    for(int i = 0;i < M;i++) {
        edges[i].first = read<int>() - 1;
        edges[i].second = read<int>() - 1;
    }
    SegmentTree **strees = new SegmentTree*[M + 1];
    strees[0] = new SegmentTree(MIN_VAL_RANGE,MAX_VAL_RANGE);
    for(int i = 0;i < M;i++) {
        int result = 0;
        Edge &tmpEdge = edges[i];
        if(tmpEdge.first == tmpEdge.second) {
            result = i + 1;
        }else if(lct.getRoot(tmpEdge.first) == lct.getRoot(tmpEdge.second)) {
            result = lct.getMinSign(tmpEdge.first,tmpEdge.second) + 1;
            lct.cut(edges[result - 1].first,result + N - 1);
            lct.cut(result + N - 1,edges[result - 1].second);
            lct.link(tmpEdge.first,i + N);
            lct.link(i + N,tmpEdge.second);
        }else {
            lct.link(tmpEdge.first,i + N);
            lct.link(i + N,tmpEdge.second);
        }
        strees[i + 1] = strees[i]->copy();
        strees[i + 1]->insert(result);
    }
    int lastAns = 0;
    while(K--) {
        int l = read<int>(),r = read<int>();
        if(type == 1) {
            l ^= lastAns;
            r ^= lastAns;
        }
        lastAns = N - SegmentTree::queryLessThan(strees[r],strees[l - 1],l);
        printf("%d\n",lastAns);
    }
    return 0;
}
