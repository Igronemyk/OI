#include <cstdio>
#include <algorithm>

using namespace std;

inline int readInt(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0'){if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0'){result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

inline long long readLong(){
    long long result = 0;
    int f = 1;char c = getchar();
    while(c > '9' || c < '0'){if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0'){result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

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
    SegmentTree(long long *value,int n){
        root = new Node(0,n - 1);
        build(value,root);
    }

    void build(long long *value,Node *now){
        if(now->isLeafNode()){
            now->sum = value[now->left];
            return;
        }
        int mid = (now->left + now->right) >> 1;
        Node *leftChild = new Node(now->left,mid);
        now->leftChild = leftChild;
        build(value,leftChild);
        Node *rightChild = new Node(mid + 1,now->right);
        now->rightChild = rightChild;
        build(value,rightChild);
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

int main(){
    int N = readInt(),M = readInt();
    long long *value = new long long[N];
    for(int i = 0;i < N;i++){
        value[i] = readLong();
    }
    SegmentTree st(value,N);
    while(M--){
        int opt = readInt();
        if(opt == 1){
            int x = readInt(),y = readInt();
            long long k = readLong();
            x--;y--;
            st.add(x,y,k);
        }else if(opt == 2){
            int x = readInt(),y = readInt();
            x--;y--;
            printf("%lld\n",st.get(x,y));
        }
    }
    return 0;
}
