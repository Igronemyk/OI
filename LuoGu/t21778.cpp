#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e5;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Operation {
    int pos,val,flag;

    Operation() : pos(0) , val(0) , flag(0) { }

    Operation(int pos,int val,int flag) : pos(pos) , val(val) , flag(flag) { }

    bool operator < (const Operation &otherOperation) const {
        return pos < otherOperation.pos;
    }
};

struct SegmentTree {
    struct Node {
        Node *ch[2];
        int maxValue,maxPos;

        Node() : maxValue(0) , maxPos(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;
    int left,right;

    SegmentTree(int left,int right) : left(left) , right(right) {
        root = new Node();
        build(root,left,right);
    }

    void updateInfo(Node *now) {
        if(now->ch[0]->maxValue == now->ch[1]->maxValue) {
            now->maxValue = now->ch[0]->maxValue;
            now->maxPos = min(now->ch[0]->maxPos,now->ch[1]->maxPos);
        }else if(now->ch[0]->maxValue > now->ch[1]->maxValue) {
            now->maxValue = now->ch[0]->maxValue;
            now->maxPos = now->ch[0]->maxPos;
        }else {
            now->maxValue = now->ch[1]->maxValue;
            now->maxPos = now->ch[1]->maxPos;
        }
    }

    void build(Node *now,int left,int right) {
        if(left == right) {
            now->maxValue = 0;
            now->maxPos = left;
            return;
        }
        int mid = (left + right) >> 1;
        now->ch[0] = new Node();
        build(now->ch[0],left,mid);
        now->ch[1] = new Node();
        build(now->ch[1],mid + 1,right);
        updateInfo(now);
    }

    void update(int pos,int val) {
        update(root,pos,left,right,val);
    }

    void update(Node *now,int pos,int left,int right,int val) {
        if(left == right) {
            now->maxValue += val;
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            update(now->ch[0],pos,left,mid,val);
        }else {
            update(now->ch[1],pos,mid + 1,right,val);
        }
        updateInfo(now);
    }

    pair<int,int> getResult() {
        return make_pair(root->maxValue,root->maxPos);
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    SegmentTree *stree = new SegmentTree(0,MAX_VAL_RANGE);
    Operation *ops = new Operation[m * 2];
    int nowSize = 0;
    for(int i = 0;i < m;i++) {
        int l = read<int>(),r = read<int>(),k = read<int>();
        ops[nowSize++] = Operation(l,k,1);
        ops[nowSize++] = Operation(r + 1,k,-1);
    }
    sort(ops,ops + nowSize);
    int nowPos = 0;
    for(int i = 1;i <= n;i++) {
        while(nowPos < nowSize && ops[nowPos].pos == i) {
            stree->update(ops[nowPos].val,ops[nowPos].flag);
            nowPos++;
        }
        pair<int,int> result = stree->getResult();
        if(result.first == 0) {
            printf("%d\n",-1);
        }else {
            printf("%d\n",result.second);
        }
    }
    return 0;
}
