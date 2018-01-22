#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentTree {
    struct Node {
        int left,right,val;
        Node *leftChild,*rightChild;
        int nowVersion;

        Node() : left(-1) , right(-1) , val(val) , leftChild(NULL) , rightChild(NULL) , nowVersion(-1) { }
        Node(int left,int right) : left(left) , right(right) , val(val) , leftChild(NULL) , rightChild(NULL) , nowVersion(0) { }
        Node(int left,int right,int val,Node *leftChild,Node *rightChild,int nowVersion) : left(left) , right(right) , val(val) , leftChild(leftChild) , rightChild(rightChild) , nowVersion(nowVersion)  { }

        bool isLeafNode() {
            return left == right;
        }

        Node *copy(int newVersion) {
            return new Node(left,right,val,leftChild,rightChild,newVersion);
        }

    };

    int nowVersion;

    Node *root;

    SegmentTree(int *values,int n) : nowVersion(0) {
        root = new Node(0,n - 1);
        build(root,values);
    }

    SegmentTree(int nowVersion,Node *root) : nowVersion(nowVersion) , root(root) { }

    void build(Node *now,int *values) {
        if(now->isLeafNode()) {
            now->val = values[now->left];
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild,values);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild,values);
    }

    void update(int pos,int val) {
        update(root,pos,val);
    }

    void update(Node *now,int pos,int val) {
        if(now->isLeafNode()) {
            now->val = val;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            if(now->leftChild->nowVersion < nowVersion) {
                now->leftChild = now->leftChild->copy(nowVersion);
            }
            update(now->leftChild,pos,val);
        }else {
            if(now->rightChild->nowVersion < nowVersion) {
                now->rightChild = now->rightChild->copy(nowVersion);
            }
            update(now->rightChild,pos,val);
        }
    }

    int getValue(int pos) {
        return getValue(root,pos);
    }

    int getValue(Node *now,int pos) {
        if(now->isLeafNode()) {
            return now->val;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            return getValue(now->leftChild,pos);
        }else {
            return getValue(now->rightChild,pos);
        }
    }

    SegmentTree *copy(int newVersion) {
        return new SegmentTree(newVersion,root->copy(newVersion));
    }

};

struct BCS {
    SegmentTree **stree;
    int nowVersion;
    BCS(int maxVersion,int size) : nowVersion(0) {
        stree = new SegmentTree*[maxVersion + 1];
        int *values = new int[size];
        for(int i = 0;i < size;i++) {
            values[i] = i;
        }
        stree[0] = new SegmentTree(values,size);
    }

    int getFather(int pos) {
        int tmpFather = stree[nowVersion]->getValue(pos);
        if(pos == tmpFather) return pos;
        tmpFather = getFather(tmpFather);
        stree[nowVersion]->update(pos,tmpFather);
        return tmpFather;
    }

    void updateVersion(int srcVersion) {
        stree[nowVersion + 1] = stree[srcVersion]->copy(nowVersion + 1);
        nowVersion++;
    }

    void merge(int u,int v) {
        updateVersion(nowVersion);
        int fatherU = getFather(u),fatherV = getFather(v);
        if(fatherU == fatherV) return;
        stree[nowVersion]->update(fatherU,fatherV);
    }

    void rollBack(int oldVersion) {
        updateVersion(oldVersion);
    }

    bool isLinked(int u,int v) {
        updateVersion(nowVersion);
        int fatherU = getFather(u),fatherV = getFather(v);
        return fatherU == fatherV;
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    BCS bcset(m,n);
    while(m--) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int u = read<int>(),v = read<int>();
                u--; v--;
                bcset.merge(u,v);
                break;
            }
            case 2: {
                int oldVersion = read<int>();
                bcset.rollBack(oldVersion);
                break;
            }
            case 3: {
                int u = read<int>(),v = read<int>();
                u--; v--;
                printf("%d\n",bcset.isLinked(u,v));
            }
        }
    }
    return 0;
}
