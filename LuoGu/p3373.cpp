#include <cstdio>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *=- 1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentTree {
    struct Node {
        Node *leftChild,*rightChild;
        int left,right;
        long long value,lazyAdd,lazyMulti;
        Node() : lazyAdd(-1) , lazyMulti(-1) , value(-1) , left(-1) , right(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right) : lazyAdd(0) , lazyMulti(1) , value(0) , left(left) , right(right) , leftChild(NULL) , rightChild(NULL) { }

        bool isLeafNode() {
            return left == right;
        }

        bool hasLazyTag() {
            return (lazyAdd != 0 || lazyMulti != 1);
        }
    };
    Node *root;
    int p;

    SegmentTree(int *values,int size,int p) : p(p) {
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

    void add(int left,int right,int val) {
        return add(left,right,val,root);
    }

    void multi(int left,int right,int val) {
        return multi(left,right,val,root);
    }

    int query(int left,int right) {
        return query(left,right,root);
    }

    void add(int left,int right,int val,Node *now) {
        if(now->left == left && now->right == right) {
            now->value = (now->value + (now->right - now->left + 1) * val) % p;
            if(!now->isLeafNode()) {
                now->lazyAdd = (now->lazyAdd + val) % p;
            }
            return;
        }
        if(now->hasLazyTag()) {
            pushDown(now);
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            add(left,right,val,now->leftChild);
        }else {
            if(left > mid) {
                add(left,right,val,now->rightChild);
            }else {
                add(left,mid,val,now->leftChild);
                add(mid + 1,right,val,now->rightChild);
            }
        }
        updateInfo(now);
    }

    void multi(int left,int right,int val,Node *now) {
        if(now->left == left && now->right == right) {
            now->value = (now->value * val) % p;
            if(!now->isLeafNode()) {
                now->lazyAdd = (now->lazyAdd * val) % p;
                now->lazyMulti = (now->lazyMulti * val) % p;
            }
            return;
        }
        if(now->hasLazyTag()) {
            pushDown(now);
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            multi(left,right,val,now->leftChild);
        }else {
            if(left > mid) {
                multi(left,right,val,now->rightChild);
            }else {
                multi(left,mid,val,now->leftChild);
                multi(mid + 1,right,val,now->rightChild);
            }
        }
        updateInfo(now);
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
                return (query(left,mid,now->leftChild) + query(mid + 1,right,now->rightChild)) % p;
            }
        }
    }

    void updateTag(long long lazyAdd,long long lazyMulti,Node *now) {
        now->value = (now->value * lazyMulti + lazyAdd * (now->right - now->left + 1)) % p;
        if(!now->isLeafNode()) {
            now->lazyMulti = (now->lazyMulti * lazyMulti) % p;
            now->lazyAdd = (now->lazyAdd * lazyMulti + lazyAdd) % p;
        }
    }

    void pushDown(Node *now) {
        updateTag(now->lazyAdd,now->lazyMulti,now->leftChild);
        updateTag(now->lazyAdd,now->lazyMulti,now->rightChild);
        now->lazyAdd = 0;
        now->lazyMulti = 1;
    }

    void updateInfo(Node *now) {
        now->value = (now->leftChild->value + now->rightChild->value) % p;
    }

};

int main() {
    int N = read<int>(),M = read<int>(),P = read<int>();
    int *values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    SegmentTree stree(values,N,P);
    while(M--) {
        int opt = read<int>(),x = read<int>(),y = read<int>();
        x--; y--;
        switch(opt) {
            case 1: {
                int k = read<int>();
                stree.multi(x,y,k);
                break;
            }
            case 2: {
                int k = read<int>();
                stree.add(x,y,k);
                break;
            }
            case 3: {
                printf("%d\n",stree.query(x,y));
                break;
            }
        }
    }
    return 0;
}
