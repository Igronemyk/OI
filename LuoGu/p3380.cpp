#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int INF = 2147483647;
const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 1e8;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <='9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Treap {
    struct Node {
        Node *childs[2];
        int value,priority,size;

        Node() : value(-1) , priority(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value) : value(value) , priority(rand()) , size(1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority > b->priority) {
            a->childs[1] = merge(a->childs[1],b);
            updateInfo(a);
            return a;
        }else {
            b->childs[0] = merge(a,b->childs[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->childs[0])) {
            result = split(now->childs[0],k);
            now->childs[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - 1);
            now->childs[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value < value) {
                result += getSize(now->childs[0]) + 1;
                now = now->childs[1];
            }else {
                now = now->childs[0];
            }
        }
        return result;
    }

    int upperCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value <= value) {
                result += getSize(now->childs[0]) + 1;
                now = now->childs[1];
            }else {
                now = now->childs[0];
            }
        }
        return result;
    }

    Node *findKth(int rank) {
        Node *now = root;
        while(now != NULL) {
            int leftChildSize = getSize(now->childs[0]);
            if(rank == leftChildSize) {
                break;
            }else if(rank < leftChildSize) {
                now = now->childs[0];
            }else {
                rank -= leftChildSize + 1;
                now = now->childs[1];
            }
        }
        return now;
    }

    void insert(int value) {
        int pos = lowerCount(value);
        DRoot tmp = split(root,pos);
        Node *newNode = new Node(value);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }

    void remove(int value) {
        int pos = lowerCount(value);
        DRoot tmp = split(root,pos);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    Node *getPrecursor(int value) {
        return findKth(lowerCount(value) - 1);
    }

    Node *getSuccessor(int value) {
        return findKth(upperCount(value));
    }

    int getPrecursorVal(int value) {
        Node *precursor = getPrecursor(value);
        if(precursor == NULL) return -INF;
        return precursor->value;
    }

    int getSuccessorVal(int value) {
        Node *successor = getSuccessor(value);
        if(successor == NULL) return INF;
        return successor->value;
    }

};

struct SegmentTree {
    struct Node {
        Node *leftChild,*rightChild;
        Treap *treap;
        int left,right;

        Node() : leftChild(NULL) , rightChild(NULL) , treap(NULL) , left(0) , right(0) { }

        Node(int left,int right) : leftChild(NULL) , rightChild(NULL) , treap(new Treap()) , left(left) , right(right) { }
    };

    Node *root;

    SegmentTree(int size) {
        root = new Node(0,size - 1);
        build(root);
    }

    void build(Node *now) {
        if(now->left == now->right) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild);
    }

    void insert(int pos,int value) {
        insert(root,pos,value);
    }

    void insert(Node *now,int pos,int value) {
        now->treap->insert(value);
        if(now->left == pos && now->right == pos) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            insert(now->leftChild,pos,value);
        }else {
            insert(now->rightChild,pos,value);
        }
    }

    void remove(int pos,int value) {
        remove(root,pos,value);
    }

    void remove(Node *now,int pos,int value) {
        now->treap->remove(value);
        if(now->left == pos && now->right == pos) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            remove(now->leftChild,pos,value);
        }else {
            remove(now->rightChild,pos,value);
        }
    }

    int queryLessThan(int left,int right,int value) {
        return queryLessThan(root,left,right,value);
    }

    int queryLessThan(Node *now,int left,int right,int value) {
        if(now->left == left && now->right == right) {
            return now->treap->lowerCount(value);
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryLessThan(now->leftChild,left,right,value);
            }else {
                return queryLessThan(now->leftChild,left,mid,value) + queryLessThan(now->rightChild,mid + 1,right,value);
            }
        }else {
            return queryLessThan(now->rightChild,left,right,value);
        }
    }

    int queryPrecursor(int left,int right,int value) {
        return queryPrecursor(root,left,right,value);
    }

    int queryPrecursor(Node *now,int left,int right,int value) {
        if(now->left == left && now->right == right) {
            return now->treap->getPrecursorVal(value);
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryPrecursor(now->leftChild,left,right,value);
            }else {
                return max(queryPrecursor(now->leftChild,left,mid,value),queryPrecursor(now->rightChild,mid + 1,right,value));
            }
        }else {
            return queryPrecursor(now->rightChild,left,right,value);
        }
    }

    int querySuccessor(int left,int right,int value) {
        return querySuccessor(root,left,right,value);
    }

    int querySuccessor(Node *now,int left,int right,int value) {
        if(now->left == left && now->right == right) {
            return now->treap->getSuccessorVal(value);
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return querySuccessor(now->leftChild,left,right,value);
            }else {
                return min(querySuccessor(now->leftChild,left,mid,value),querySuccessor(now->rightChild,mid + 1,right,value));
            }
        }else {
            return querySuccessor(now->rightChild,left,right,value);
        }
    }

    /*
    int getValueByRank(int left,int right,int rank) {
        int leftValue = MIN_VAL_RANGE,rightValue = MAX_VAL_RANGE;
        while(leftValue < rightValue) {
            int mid = (leftValue + rightValue) >> 1;
            if(queryLessThan(left,right,mid) + 1 <= rank) {
                leftValue = mid + 1;
            }else {
                rightValue = mid;
            }
        }
        return leftValue - 1;
    }*/

    int getValueByRank(int left,int right,int rank) {
        int leftValue = MIN_VAL_RANGE,rightValue = MAX_VAL_RANGE,ans = -INF;
        while(leftValue <= rightValue) {
            int mid = (leftValue + rightValue) >> 1;
            if(queryLessThan(left,right,mid) + 1 <= rank) {
                ans = max(ans,mid);
                leftValue = mid + 1;
            }else {
                rightValue = mid - 1;
            }
        }
        return ans;
    }
};

int main() {
    srand(123456);
    int n = read<int>(),m = read<int>(),*values = new int[n];
    SegmentTree segtree(n);
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        segtree.insert(i,values[i]);
    }
    while(m--) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",segtree.queryLessThan(l,r,k) + 1);
                break;
            }
            case 2: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",segtree.getValueByRank(l,r,k));
                break;
            }
            case 3: {
                int pos = read<int>(),k = read<int>();
                pos--;
                segtree.remove(pos,values[pos]);
                values[pos] = k;
                segtree.insert(pos,values[pos]);
                break;
            }
            case 4: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",segtree.queryPrecursor(l,r,k));
                break;
            }
            case 5: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",segtree.querySuccessor(l,r,k));
                break;
            }
        }
    }
    return 0;
}
