#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0'; c = getchar();}
    return result * f;
}

struct SegmentTree {
    struct Node {
        int left,right,value;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , value(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right) : left(left) , right(right) , value(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right,int value,Node *leftChild,Node *rightChild) : left(left) , right(right) , value(value) , leftChild(leftChild) , rightChild(rightChild) { }

        bool isLeafNode() {
            return left == right;
        }

        Node * copy() {
            return new Node(left,right,value,leftChild,rightChild);
        }

    };

    Node *root;
    SegmentTree(int *values,int size) {
        root = new Node(0,size - 1);
        build(values,root);
    }

    SegmentTree(Node *root) : root(root) { }

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
    }

    void update(int pos,int val) {
        update(root,pos,val);
    }

    void update(Node *now,int pos,int val) {
        if(now->isLeafNode()) {
            now->value = val;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            now->leftChild = now->leftChild->copy();
            update(now->leftChild,pos,val);
        }else {
            now->rightChild = now->rightChild->copy();
            update(now->rightChild,pos,val);
        }
    }

    int get(int pos) {
        return get(root,pos);
    }

    int get(Node *now,int pos) {
        if(now->isLeafNode()) {
            return now->value;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            return get(now->leftChild,pos);
        }else {
            return get(now->rightChild,pos);
        }

    }

    SegmentTree * copy() {
        return new SegmentTree(root->copy());
    }

};

int main() {
    int N = read<int>(),M = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    SegmentTree **versions = new SegmentTree*[M + 1];
    versions[0] = new SegmentTree(values,N);
    for(int i = 1;i <= M;i++) {
        int version = read<int>(),opt = read<int>(),location = read<int>();
        location--;
        versions[i] = versions[version]->copy();
        switch(opt) {
            case 1: {
                int value = read<int>();
                versions[i]->update(location,value);
                break;
            }
            case 2: {
                printf("%d\n",versions[i]->get(location));
                break;
            }
        }
    }
    return 0;
}
