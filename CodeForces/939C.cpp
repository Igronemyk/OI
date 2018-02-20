#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

struct SegmentTree{
    struct Node{
        Node *leftChild,*rightChild;
        int left,right;
        long long addValue,sum;
        Node() : leftChild(NULL),rightChild(NULL),left(-1),right(-1),addValue(-1),sum(-1) {}
        Node(int left,int right) : leftChild(NULL),rightChild(NULL),left(left),right(right),addValue(0),sum(0) {}
        bool isLeafNode(){
            return left == right;
        }
    };
    Node *root;
    SegmentTree(int n){
        root = new Node(1,n);
        build(root);
    }

    void build(Node *now){
        if(now->isLeafNode()){
            now->sum = 0;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        Node *leftChild = new Node(now->left,mid);
        now->leftChild = leftChild;
        build(leftChild);
        Node *rightChild = new Node(mid + 1,now->right);
        now->rightChild = rightChild;
        build(rightChild);
        updateInfo(now);
    }

    void updateInfo(Node *now){
        now->sum = now->leftChild->sum + now->rightChild->sum;
    }

    void pushDown(Node *now){
        now->leftChild->sum += (now->leftChild->right - now->leftChild->left + 1) * now->addValue;
        now->rightChild->sum += (now->rightChild->right - now->rightChild->left + 1) * now->addValue;
        if(!now->leftChild->isLeafNode()){
            now->leftChild->addValue += now->addValue;
        }
        if(!now->rightChild->isLeafNode()){
            now->rightChild->addValue += now->addValue;
        }
        now->addValue = 0;
    }

    void add(int left,int right,long long value){
        add(left,right,value,root);
    }

    long long get(int left,int right){
        return get(left,right,root);
    }

    void add(int left,int right,long long value,Node *now){
        if(now->left == left && now->right == right){
            now->sum += (now->right - now->left + 1) * value;
            if(!now->isLeafNode()) now->addValue += value;
            return;
        }
        if(now->addValue != 0) pushDown(now);
        int mid = (now->left + now->right) >> 1;
        if(left <= mid){
            if(right <= mid){
                add(left,right,value,now->leftChild);
            }else{
                add(left,mid,value,now->leftChild);
                add(mid + 1,right,value,now->rightChild);
            }
        }else{
            add(left,right,value,now->rightChild);
        }
        updateInfo(now);
    }

    long long get(int left,int right,Node *now){
        if(now->left == left && now->right == right){
            return now->sum;
        }
        if(now->addValue != 0) pushDown(now);
        int mid = (now->left + now->right) >> 1;
        if(left <= mid){
            if(right <= mid){
                return get(left,right,now->leftChild);
            }else{
                return get(left,mid,now->leftChild) + get(mid + 1,right,now->rightChild);
            }
        }else{
            return get(left,right,now->rightChild);
        }
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,s,f;
    cin >> n;
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        cin >> values[i];
    }
    cin >> s >> f;
    f--;
    SegmentTree stree(n);
    for(int i = 0;i < n;i++) {
        int tmpStart = s - i,tmpEnd = f - i;
        if(tmpStart <= 0) tmpStart += n;
        if(tmpEnd <= 0) tmpEnd += n;
        if(tmpStart <= tmpEnd) {
            stree.add(tmpStart,tmpEnd,values[i]);
        }else {
            stree.add(tmpStart,n,values[i]);
            stree.add(1,tmpEnd,values[i]);
        }
    }
    long long maxValue = -1,result = -1;
    for(int i = 1;i <= n;i++) {
        long long tmpValue = stree.get(i,i);
        if(tmpValue > maxValue) {
            maxValue = tmpValue;
            result = i;
        }
    }
    cout << result << endl;
    return 0;
}

