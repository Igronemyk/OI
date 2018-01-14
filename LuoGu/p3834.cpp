#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0'; c = getchar();}
    return result * f;
}

struct Discreter {
    int *values,length;
    Discreter(int *values,int size) {
        this->values = new int[size];
        memcpy(this->values,values,sizeof(int) * size);
        sort(this->values,this->values + size);
        length = unique(this->values,this->values + size) - this->values;
    }

    int getDiscretedValue(int value) {
        return lower_bound(values,values + length,value) - values;
    }

    int getSize() {
        return length;
    }

    int getValue(int pos) {
        return values[pos];
    }
};

struct SegmentTree {
    struct Node {
        int left,right,size;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , size(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right) : left(left) , right(right) , size(0) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right,int size,Node *leftChild,Node *rightChild) : left(left) , right(right) , size(size) , leftChild(leftChild) , rightChild(rightChild) { }

        bool isLeafNode() {
            return left == right;
        }

        Node * copy() {
            return new Node(left,right,size,leftChild,rightChild);
        }

    };

    Node *root;
    SegmentTree(int size) {
        root = new Node(0,size - 1);
        build(root);
    }

    SegmentTree(Node *root) : root(root) { }

    void build(Node *now) {
        if(now->isLeafNode()) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild);
    }

    void update(int pos,int val) {
        update(root,pos,val);
    }

    void update(Node *now,int pos,int val) {
        if(now->isLeafNode()) {
            now->size += val;
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
        updateInfo(now);
    }

    int query(int rank,SegmentTree *oldVersion) {
        return query(root,oldVersion->root,rank);
    }

    int query(Node *now,Node *oldVersion,int rank) {
        if(now->isLeafNode()) {
            return now->left;
        }
        int nowRank = now->leftChild->size - oldVersion->leftChild->size;
        if(nowRank >= rank) {
            return query(now->leftChild,oldVersion->leftChild,rank);
        }else {
            return query(now->rightChild,oldVersion->rightChild,rank - nowRank);
        }
    }

    void updateInfo(Node *now) {
        now->size = now->leftChild->size + now->rightChild->size;
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
    SegmentTree **versions = new SegmentTree*[N + 1];
    Discreter *discreter = new Discreter(values,N);
    versions[0] = new SegmentTree(discreter->getSize());
    for(int i = 1;i <= N;i++) {
        int val = discreter->getDiscretedValue(values[i - 1]);
        versions[i] = versions[i - 1]->copy();
        versions[i]->update(val,1);
    }
    for(int i = 0;i < M;i++) {
        int left = read<int>(),right = read<int>(),k = read<int>();
        printf("%d\n",discreter->getValue(versions[right]->query(k,versions[left - 1])));
    }
    return 0;
}
