#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 50010;
const int MAXM = 50010;

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
        unsigned int cnt,lazy;

        Node() : cnt(0) , lazy(0) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;

    SegmentTree() {
        root = new Node();
    }

    static int getCnt(Node *now) {
        if(now == NULL) return 0;
        return now->cnt;
    }

    void updateInfo(Node *now,int left,int right) {
        now->cnt = getCnt(now->ch[0]) + getCnt(now->ch[1]) + now->lazy * (right - left + 1);
    }

    void update(int l,int r,int value) {
        update(root,1,MAXN,l,r,value);
    }

    void update(Node *now,int left,int right,int l,int r,int value) {
        if(left == l && right == r) {
            now->lazy += value;
            updateInfo(now,left,right);
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                if(now->ch[0] == NULL) {
                    now->ch[0] = new Node();
                }
                update(now->ch[0],left,mid,l,r,value);
            }else {
                if(now->ch[0] == NULL) {
                    now->ch[0] = new Node();
                }
                update(now->ch[0],left,mid,l,mid,value);
                if(now->ch[1] == NULL) {
                    now->ch[1] = new Node();
                }
                update(now->ch[1],mid + 1,right,mid + 1,r,value);
            }
        }else {
            if(now->ch[1] == NULL) {
                now->ch[1] = new Node();
            }
            update(now->ch[1],mid + 1,right,l,r,value);
        }
        updateInfo(now,left,right);
    }

    unsigned int queryCnt(int l,int r) {
        return queryCnt(root,1,MAXN,l,r,0);
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


} stree;

struct Operation {
    int type,left,right,value,cnt;

    Operation() : type(0) , left(0) , right(0) , value(0) , cnt(0) { }

    Operation(int type,int left,int right,int value,int cnt) : type(type) , left(left) , right(right) , value(value) , cnt(cnt) { }
} opts[MAXM],opts1[MAXM],opts2[MAXM];

int result[MAXM];

void cdq(int left,int right,int leftRange,int rightRange) {
    if(left > right) return;
    if(leftRange == rightRange) {
        for(int i = left;i <= right;i++) {
            Operation &tmpOpt = opts[i];
            if(tmpOpt.type == 2) {
                result[tmpOpt.value] = leftRange;
            }
        }
        return;
    }
    int midRange = (leftRange + rightRange) >> 1;
    int cnt1 = 0,cnt2 = 0;
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 1) {
            if(tmpOpt.value > midRange) {
                stree.update(tmpOpt.left,tmpOpt.right,1);
                opts2[cnt2++] = tmpOpt;
            }else {
                opts1[cnt1++] = tmpOpt;
            }
        }else {
            unsigned int cnt = stree.queryCnt(tmpOpt.left,tmpOpt.right);
            if(cnt < tmpOpt.cnt) {
                tmpOpt.cnt -= cnt;
                opts1[cnt1++] = tmpOpt;
            }else {
                opts2[cnt2++] = tmpOpt;
            }
        }
    }
    for(int i = left;i <= right;i++) {
        Operation &tmpOpt = opts[i];
        if(tmpOpt.type == 1) {
            if(tmpOpt.value > midRange) {
                stree.update(tmpOpt.left,tmpOpt.right,-1);
            }
        }
    }
    copy(opts1,opts1 + cnt1,opts + left);
    copy(opts2,opts2 + cnt2,opts + left + cnt1);
    cdq(left,left + cnt1 - 1,leftRange,midRange);
    cdq(left + cnt1,right,midRange + 1,rightRange);
}

int main() {
    int N = read<int>(),M = read<int>();
    int nowIndex = 0;
    for(int i = 0;i < M;i++) {
        int opt = read<int>(),a = read<int>(),b = read<int>(),c = read<int>();
        if(opt == 1) {
            opts[i] = Operation(opt,a,b,c,-1);
        }else {
            opts[i] = Operation(opt,a,b,nowIndex++,c);
        }
    }
    cdq(0,M - 1,-N,N);
    for(int i = 0;i < nowIndex;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}
