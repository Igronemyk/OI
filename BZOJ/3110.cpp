#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>

using namespace std;

const int MIN_VAL_RANGE = -50000;
const int MAX_VAL_RANGE = 50000;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int N,M;

struct RangeSegmentTree {
    struct Node {
        Node *ch[2];
        unsigned int cnt,lazy;

        Node() : cnt(0) , lazy(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;

    RangeSegmentTree() {
        root = new Node();
    }

    static int getCnt(Node *now) {
        if(now == NULL) return 0;
        return now->cnt;
    }

    void updateInfo(Node *now,int left,int right) {
        now->cnt = getCnt(now->ch[0]) + getCnt(now->ch[1]) + now->lazy * (right - left + 1);
    }

    void update(int l,int r) {
        update(root,1,N,l,r);
    }

    void update(Node *now,int left,int right,int l,int r) {
        if(left == l && right == r) {
            now->lazy++;
            updateInfo(now,left,right);
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                if(now->ch[0] == NULL) {
                    now->ch[0] = new Node();
                }
                update(now->ch[0],left,mid,l,r);
            }else {
                if(now->ch[0] == NULL) {
                    now->ch[0] = new Node();
                }
                update(now->ch[0],left,mid,l,mid);
                if(now->ch[1] == NULL) {
                    now->ch[1] = new Node();
                }
                update(now->ch[1],mid + 1,right,mid + 1,r);
            }
        }else {
            if(now->ch[1] == NULL) {
                now->ch[1] = new Node();
            }
            update(now->ch[1],mid + 1,right,l,r);
        }
        updateInfo(now,left,right);
    }

    unsigned int queryCnt(int l,int r) {
        return queryCnt(root,1,N,l,r,0);
    }

    unsigned int queryCnt(Node *now,int left,int right,int l,int r,unsigned int lazyInfo) {
        if(now == NULL) return lazyInfo * (r - l + 1);
        if(left == l && right == r) {
            return now->cnt + lazyInfo * (right - left + 1);
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return queryCnt(now->ch[0],left,mid,l,r,lazyInfo + now->lazy);
            }else {
                return queryCnt(now->ch[0],left,mid,l,mid,lazyInfo + now->lazy) + queryCnt(now->ch[1],mid + 1,right,mid + 1,r,lazyInfo + now->lazy);
            }
        }else {
            return queryCnt(now->ch[1],mid + 1,right,l,r,lazyInfo + now->lazy);
        }
    }


};

struct ValueSegmentTree {
    struct Node {
        Node *ch[2];
        RangeSegmentTree *rst;

        Node() {
            rst = new RangeSegmentTree();
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;

    ValueSegmentTree() {
        root = new Node();
    }

    void insert(int pos,int l,int r) {
        insert(root,MIN_VAL_RANGE,MAX_VAL_RANGE,pos,l,r);
    }

    void insert(Node *now,int left,int right,int pos,int l,int r) {
        now->rst->update(l,r);
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            if(now->ch[0] == NULL) {
                now->ch[0] = new Node();
            }
            insert(now->ch[0],left,mid,pos,l,r);
        }else {
            if(now->ch[1] == NULL) {
                now->ch[1] = new Node();
            }
            insert(now->ch[1],mid + 1,right,pos,l,r);
        }
    }

    static unsigned int queryInfo(Node *now,int l,int r) {
        if(now == NULL) return 0;
        return now->rst->queryCnt(l,r);
    }

    int getKth(int l,int r,int k) {
        return getKth(root,MIN_VAL_RANGE,MAX_VAL_RANGE,l,r,k);
    }

    int getKth(Node *now,int left,int right,int l,int r,int k) {
        if(left == right) {
            return left;
        }
        unsigned int cnt = queryInfo(now->ch[1],l,r);
        int mid = (left + right) >> 1;
        if(cnt < static_cast<unsigned int>(k)) {
            return getKth(now->ch[0],left,mid,l,r,k - cnt);
        }else {
            return getKth(now->ch[1],mid + 1,right,l,r,k);
        }
    }

};

int main() {
    N = read<int>();
    M = read<int>();
    ValueSegmentTree *vst = new ValueSegmentTree();
    while(M--) {
        int opt = read<int>(),a = read<int>(),b = read<int>(),c = read<int>();
        if(opt == 1) {
            vst->insert(c,a,b);
        }else {
            printf("%d\n",vst->getKth(a,b,c));
        }
    }
    return 0;
}
