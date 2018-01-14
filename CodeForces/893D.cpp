#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct SegmentTree {
    struct Node {
        int left,right,lazy,value,maxValue;
        Node *leftChild,*rightChild;
        Node() : left(-1) , right(-1) , lazy(-1) , value(-1) , maxValue(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int left,int right) : left(left) , right(right) , lazy(0) , value(0) , maxValue(0) , leftChild(NULL) , rightChild(NULL) { }
        bool hasLazyTag() {
            return lazy != 0;
        }
        bool isLeafNode() {
            return left == right;
        }
    };

    Node *root;

    SegmentTree(int *values,int size) {
        root = new Node(0,size - 1);
        build(values,size,root);
    }

    void build(int *values,int size,Node *now) {
        if(now->left == now->right) {
            now->value = values[now->left];
            now->maxValue = now->value;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(values,size,now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(values,size,now->rightChild);
        updateInfo(now);
    }

    int getMax(int left,int right) {
        return getMax(left,right,root);
    }

    int getMax(int left,int right,Node *now) {
        if(now->left == left && now->right == right) {
            return now->maxValue;
        }
        if(now->hasLazyTag()) pushDown(now);
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            return getMax(left,right,now->leftChild);
        }else {
            if(left > mid) {
                return getMax(left,right,now->rightChild);
            }else {
                return max(getMax(left,mid,now->leftChild),getMax(mid + 1,right,now->rightChild));
            }
        }
    }

    void update(int left,int right,int value) {
        update(left,right,value,root);
    }

    void update(int left,int right,int value,Node *now) {
        if(now->left == left && now->right == right) {
            updateTag(value,now);
            return;
        }
        if(now->hasLazyTag()) pushDown(now);
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            update(left,right,value,now->leftChild);
        }else {
            if(left > mid) {
                update(left,right,value,now->rightChild);
            }else {
                update(left,mid,value,now->leftChild);
                update(mid + 1,right,value,now->rightChild);
            }
        }
        updateInfo(now);
    }

    void pushDown(Node *now) {
        updateTag(now->lazy,now->leftChild);
        updateTag(now->lazy,now->rightChild);
        now->lazy = 0;
    }

    void updateTag(int value,Node *now) {
        now->value += (now->right - now->left + 1) * value;
        now->maxValue += value;
        if(!now->isLeafNode()) {
            now->lazy += value;
        }
    }

    void updateInfo(Node *now) {
        now->value = now->leftChild->value + now->rightChild->value;
        now->maxValue = max(now->leftChild->maxValue,now->rightChild->maxValue);
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,d;
    cin >> n >> d;
    int *values = new int[n],*indexValue = new int[n];
    cin >> values[0];
    indexValue[0] = values[0];
    for(int i = 1;i < n;i++) {
        cin >> values[i];
        indexValue[i] = values[i] + indexValue[i - 1];
        if(indexValue[i] > d) {
            cout << -1 << endl;
            return 0;
        }
    }
    SegmentTree stree(indexValue,n);
    bool flag = true;
    long long nowVal = 0,result = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue = values[i];
        if(tmpValue == 0) {
            if(nowVal < 0) {
                int needValue = -nowVal,maxValue = stree.getMax(i,n - 1);
                if(d - maxValue < needValue) {
                    flag = false;
                    break;
                }else {
                    result++;
                    stree.update(i,n - 1,d - maxValue);
                    nowVal += d - maxValue;
                }
            }
        }else if(tmpValue > 0) {
            nowVal += tmpValue;
            if(nowVal > d) {
                flag = false;
                break;
            }
        }else if(tmpValue < 0) {
            nowVal += tmpValue;
        }
    }
    if(!flag) {
        cout << -1 << endl;
    }else {
        cout << result << endl;
    }
    return 0;
}
