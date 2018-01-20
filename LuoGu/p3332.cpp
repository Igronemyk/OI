#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>

using namespace std;

struct SegmentTree {
    struct Node {
        int left,right;
        Node *leftChild,*rightChild;
        unsigned int sum,addValue;

        Node(int left,int right) : left(left) , right(right) , leftChild(NULL) , rightChild(NULL) , sum(0) { }

    };

    Node *root;

    int getSum(Node *now) {
        if(now == NULL) return 0;
        return now->sum;
    }

    void updateInfo(Node *now) {
        now->sum = getSum(now->leftChild) + getSum(now->rightChild) + now->addValue * (now->right - now->left + 1);
    }

    void add(int left,int right) {
        add(root,left,right);
    }

    void add(Node *now,int left,int right) {
        if(now->left > right || now->right < left) return;
        if(now->left >= left && now->right <= right) {
            now->addValue++;
        }else {
            int mid = (now->left + now->right) >> 1;
            if(now->leftChild == NULL) {
                now->leftChild = new Node(now->left,mid);
            }
            add(now->leftChild,left,right);
            if(now->rightChild == NULL) {
                now->rightChild = new Node(mid + 1,now->right);
            }
            add(now->rightChild,left,right);
        }
        updateInfo(now);
    }

    int query(int left,int right) {
        return query(root,left,right,0);
    }

    int qeuery(Node *now,int left,int right,unsigned int addValue) {
        if(now == NULL) return 0;
        if()
    }


};

int main() {
    return 0;
}
