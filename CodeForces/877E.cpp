#include <iostream>
#include <cstring>
#include <string>
#include <utility>

using namespace std;

const int MAXN = 200010;

namespace Adj {
    struct Node {
        int to,next;
    } nodes[MAXN * 2];
    int tot,heads[MAXN];

    void init() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        heads[u] = tot++;
    }

}

struct ST {
    struct Node {
        int left,right,value;
        bool lazyTag;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , value(-1) , lazyTag(false) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right) : left(left) , right(right) , value(0) , lazyTag(false) , leftChild(NULL) , rightChild(NULL) { }

        bool isLeafNode() {
            return left == right;
        }
    };
    Node *root;
    ST(int *values,int size) {
        root = new Node(0,size - 1);
        build(values,root);
    }

    void updateInfo(Node *now) {
        now->value = now->leftChild->value + now->rightChild->value;
    }

    void pushDown(Node *now) {
        now->leftChild->value = now->leftChild->right - now->leftChild->left + 1 - now->leftChild->value;
        now->rightChild->value = now->rightChild->right - now->rightChild->left + 1 - now->rightChild->value;
        if(!now->leftChild->isLeafNode()) now->leftChild->lazyTag = !now->leftChild->lazyTag;
        if(!now->rightChild->isLeafNode()) now->rightChild->lazyTag = !now->rightChild->lazyTag;
        now->lazyTag = !now->lazyTag;
    }

    void build(int *values,Node *now) {
        if(now->left == now->right) {
            now->value = values[now->left];
            return;
        }
        int mid = (now->right + now->left) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(values,now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(values,now->rightChild);
        updateInfo(now);
    }

    int get(int left,int right) {
        return get(left,right,root);
    }

    int get(int left,int right,Node *now) {
        if(now->left == left && now->right == right) {
            return now->value;
        }
        if(now->lazyTag) {
            pushDown(now);
        }
        int mid = (now->right + now->left) >> 1;
        if(right <= mid) {
            return get(left,right,now->leftChild);
        }else {
            if(left > mid) {
                return get(left,right,now->rightChild);
            }else {
                return get(left,mid,now->leftChild) + get(mid + 1,right,now->rightChild);
            }
        }
    }

    void reserve(int left,int right) {
        reserve(left,right,root);
    }

    void reserve(int left,int right,Node *now) {
        if(now->left == left && now->right == right) {
            now->value = now->right - now->left + 1 - now->value;
            if(!now->isLeafNode()) now->lazyTag = !now->lazyTag;
            return;
        }
        if(now->lazyTag) {
            pushDown(now);
        }
        int mid = (now->right + now->left) >> 1;
        if(right <= mid) {
            reserve(left,right,now->leftChild);
        }else {
            if(left > mid) {
                reserve(left,right,now->rightChild);
            }else {
                reserve(left,mid,now->leftChild);
                reserve(mid + 1,right,now->rightChild);
            }
        }
        updateInfo(now);
    }
};

using namespace Adj;

int *values,nowIndex,*weight;
pair<int,int> *rangeIndex;

void dfs(int now) {
    rangeIndex[now].first = nowIndex;
    values[nowIndex++] = weight[now];
    for(int i = heads[now];i != -1;i = nodes[i].next) {
        dfs(nodes[i].to);
    }
    rangeIndex[now].second = nowIndex - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int n;
    cin >> n;
    nowIndex = 0;
    values = new int[n];
    weight = new int[n];
    rangeIndex = new pair<int,int>[n];
    for(int i = 1;i < n;i++) {
        int father;
        cin >> father;
        father--;
        addEdge(father,i);
    }
    for(int i = 0;i < n;i++) {
        int status;
        cin >> status;
        weight[i] = status;
    }
    dfs(0);
    ST tree(values,n);
    int q;
    cin >> q;
    for(int i = 0;i < q;i++) {
        string opt;
        cin >> opt;
        int pos;
        cin >> pos;
        pos--;
        if(opt == "get") {
            cout << tree.get(rangeIndex[pos].first,rangeIndex[pos].second) << endl;
        }else if(opt == "pow") {
            tree.reserve(rangeIndex[pos].first,rangeIndex[pos].second);
        }
    }
    return 0;
}
