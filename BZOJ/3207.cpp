#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int M1 = 107;
const unsigned long long INF = 18446744073709551615UL;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentTree {
    struct Node {
        Node *ch[2];
        int cnt;

        Node() : cnt(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }

        Node(Node *lc,Node *rc,int cnt) : cnt(cnt) {
            ch[0] = lc;
            ch[1] = rc;
        }

        Node *copy() {
            return new Node(ch[0],ch[1],cnt);
        }
    };

    Node *root;
    unsigned long long left,right;

    static Node *copyNode(Node *now) {
        if(now == NULL) return new Node();
        return now->copy();
    }

    SegmentTree(unsigned long long left,unsigned long long right) : root(new Node()) , left(left) , right(right) { }

    SegmentTree(Node *root,unsigned long long left,unsigned long long right) : root(copyNode(root)) , left(left) , right(right) { }

    void insert(unsigned long long pos) {
        insert(root,left,right,pos);
    }

    void insert(Node *now,unsigned long long left,unsigned long long right,unsigned long long pos) {
        now->cnt++;
        if(left == right) return;
        unsigned long long mid = (left >> 1) + (right >> 1);
        if((left & 1) && (right & 1)) mid++;
        if(pos <= mid) {
            now->ch[0] = copyNode(now->ch[0]);
            insert(now->ch[0],left,mid,pos);
        }else {
            now->ch[1] = copyNode(now->ch[1]);
            insert(now->ch[1],mid + 1,right,pos);
        }
    }

    int getCnt(unsigned long long pos) {
        return getCnt(root,left,right,pos);
    }

    int getCnt(Node *now,unsigned long long left,unsigned long long right,unsigned long long pos) {
        if(now == NULL) return 0;
        if(left == right) {
            return now->cnt;
        }
        unsigned long long mid = (left >> 1) + (right >> 1);
        if((left & 1) && (right & 1)) mid++;
        if(pos <= mid) {
            return getCnt(now->ch[0],left,mid,pos);
        }else {
            return getCnt(now->ch[1],mid + 1,right,pos);
        }
    }

    SegmentTree *copy() {
        return new SegmentTree(root,left,right);
    }

};

int main() {
    int N = read<int>(),M = read<int>(),K = read<int>();
    unsigned long long *h = new unsigned long long[N + 1],*values = new unsigned long long[N - K + 1];
    h[0] = 0;
    for(int i = 1;i <= N;i++) {
        int tmpValue = read<int>();
        h[i] = h[i - 1] * M1 + tmpValue;
    }
    unsigned long long diffM = 1;
    for(int i = 1;i <= K;i++) diffM *= M1;
    for(int i = K;i <= N;i++) {
        int sign = i - K;
        values[sign] = h[i] - h[sign] * diffM;
    }
    SegmentTree **strees = new SegmentTree*[N + 1];
    strees[0] = new SegmentTree(0,INF);
    for(int i = 1;i <= N;i++) {
        strees[i] = strees[i - 1]->copy();
        if(i < K) continue;
        int sign = i - K;
        strees[i]->insert(values[sign]);
    }
    while(M--) {
        int left = read<int>(),right = read<int>();
        unsigned long long hashValue = 0;
        for(int i = 0;i < K;i++) hashValue = hashValue * M1 + read<int>();
        int leftSize = strees[min(right,left + K - 2)]->getCnt(hashValue),rightSize = strees[right]->getCnt(hashValue);
        printf((rightSize - leftSize > 0) ? "No\n" : "Yes\n");
    }
    return 0;
}
