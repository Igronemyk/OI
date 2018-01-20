#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <utility>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c  < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentTree {
    struct Node {
        Node *leftChild,*rightChild;
        int cnt,sum,left,right;

        Node(int left,int right) : leftChild(NULL) , rightChild(NULL) , left(left) , right(right) { }
        Node(Node *leftChild,Node *rightChild,int cnt,int sum,int left,int right) : leftChild(leftChild) , rightChild(rightChild) , cnt(cnt) , sum(sum) , left(left) , right(right) { }

        Node *copy() {
            return new Node(leftChild,rightChild,cnt,sum,left,right);
        }
    };

    Node *root;

    SegmentTree(int n) {
        root = new Node(0,n - 1);
        build(root);
    }

    SegmentTree(Node *root) {
        root = root;
    }

    void updateInfo(Node *now) {
        now->cnt = now->leftChild->cnt + now->rightChild->cnt;
    }

    void build(Node *now) {
        if(now->left == now->right) {
            now->cnt = 0;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild);
        updateInfo(now);
    }

    void add(int pos) {
        add(root,pos);
    }

    void add(Node *now,int pos) {
        if(now->left == pos && now->right == pos) {
            now->cnt++;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            now->leftChild = now->leftChild->copy();
            add(now->leftChild,pos);
        }else {
            now->rightChild = now->rightChild->copy();
            add(now->rightChild,pos);
        }
        updateInfo(now);
    }

    SegmentTree *copy() {
        return new SegmentTree(root->copy());
    }
};

struct Discreter {
    int *saveValues;
    int saveSize;
    Discreter(int *values,int size) {
        saveValues = new int[size];
        memcpy(saveValues,values,sizeof(int) * size);
        sort(saveValues,saveValues + size);
        saveSize = unique(saveValues,saveValues + size) - saveValues;
    }

    int getValue(int value) {
        return lower_bound(saveValues,saveValues + saveSize,value) - saveValues;
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
构建欧拉序
*/
void dfs(int now,int father,Graph &graph,SegmentTree *trees) {

}

int main() {
    int N = read<int>(),M = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    Discreter discreter(values,N);
    Graph graph();
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
    }
    return 0;
}
