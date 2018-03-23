#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)

using namespace std;

const int MAX_TREAP_NODE_SIZE = 3000010;
const int MAX_SEGMENT_NODE_SIZE = 400010;
const int MAXN = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getc();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getc();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getc();}
    return result * f;
}

struct TreapNode {
    int ch[2];
    int value,priority,size;

    TreapNode() : value(0) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : value(value) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value) {
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    static void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    static int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(tn[a].ch[1],b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,tn[b].ch[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(tn[now].ch[0],k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int now = root,result = 0;
        while(now != 0) {
            if(tn[now].value < value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    int upperCount(int value) {
        int now = root,result = 0;
        while(now != 0) {
            if(tn[now].value > value) {
                result += tn[tn[now].ch[1]].size + 1;
                now = tn[now].ch[0];
            }else {
                now = tn[now].ch[1];
            }
        }
        return result;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    void print() {
        print(root);
        printf("\n");
    }

    void print(int now) {
        if(now == 0) return;
        print(tn[now].ch[0]);
        printf("%d ",tn[now].value);
        print(tn[now].ch[1]);
    }

};

struct SegmentNode {
    int ch[2];
    int left,right;
    Treap treap;

    SegmentNode() : left(-1) , right(-1) {
        ch[0] = 0;
        ch[1] = 0;
        treap = Treap();
    }

    SegmentNode(int left,int right) : left(left) , right(right) {
        ch[0] = 0;
        ch[1] = 0;
        treap = Treap();
    }

    bool isLeafNode() {
        return left == right;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root;

    static int newNode(int left,int right) {
        sn[++segmentSize] = SegmentNode(left,right);
        return segmentSize;
    }

    SegmentTree(int size) {
        root = newNode(0,size - 1);
        build(root);
    }

    void build(int now) {
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        sn[now].ch[0] = newNode(sn[now].left,mid);
        build(sn[now].ch[0]);
        sn[now].ch[1] = newNode(mid + 1,sn[now].right);
        build(sn[now].ch[1]);
    }

    void insert(int pos,int val) {
        insert(root,pos,val);
    }

    void insert(int now,int pos,int val) {
        sn[now].treap.insert(val);
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            insert(sn[now].ch[0],pos,val);
        }else {
            insert(sn[now].ch[1],pos,val);
        }
    }

    void remove(int pos,int val) {
        remove(root,pos,val);
    }

    void remove(int now,int pos,int val) {
        sn[now].treap.remove(val);
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            remove(sn[now].ch[0],pos,val);
        }else {
            remove(sn[now].ch[1],pos,val);
        }
    }

    int queryLessThan(int left,int right,int val) {
        return queryLessThan(root,left,right,val);
    }

    int queryLessThan(int now,int left,int right,int val) {
        if(sn[now].left == left && sn[now].right == right) {
            return sn[now].treap.lowerCount(val);
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryLessThan(sn[now].ch[0],left,right,val);
            }else {
                return queryLessThan(sn[now].ch[0],left,mid,val) + queryLessThan(sn[now].ch[1],mid + 1,right,val);
            }
        }else {
            return queryLessThan(sn[now].ch[1],left,right,val);
        }
    }

    int queryGreaterThan(int left,int right,int val) {
        return queryGreaterThan(root,left,right,val);
    }

    int queryGreaterThan(int now,int left,int right,int val) {
        if(sn[now].left == left && sn[now].right == right) {
            return sn[now].treap.upperCount(val);
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryGreaterThan(sn[now].ch[0],left,right,val);
            }else {
                return queryGreaterThan(sn[now].ch[0],left,mid,val) + queryGreaterThan(sn[now].ch[1],mid + 1,right,val);
            }
        }else {
            return queryGreaterThan(sn[now].ch[1],left,right,val);
        }
    }
};

int signs[MAXN],querys[MAXN];
long long results[MAXN];

bool isDeleted[MAXN];

int main() {
    srand(123456);
    int n = read<int>(),m = read<int>();
    SegmentTree stree(n);
    long long result = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        signs[tmpValue] = i;
    }
    for(int i = 0;i < m;i++) {
        querys[i] = read<int>();
        isDeleted[querys[i]] = true;
    }
    for(int i = 1;i <= n;i++) {
        if(isDeleted[i]) continue;
        stree.insert(signs[i],i);
        if(signs[i] - 1 >= 0) {
            result += stree.queryGreaterThan(0,signs[i] - 1,i);
        }
        if(signs[i] + 1 <= n - 1) {
            result += stree.queryLessThan(signs[i] + 1,n - 1,i);
        }
    }
    for(int i = m - 1;i >= 0;i--) {
        stree.insert(signs[querys[i]],querys[i]);
        if(signs[querys[i]] - 1 >= 0) {
            result += stree.queryGreaterThan(0,signs[querys[i]] - 1,querys[i]);
        }
        if(signs[querys[i]] + 1 <= n - 1) {
            result += stree.queryLessThan(signs[querys[i]] + 1,n - 1,querys[i]);
        }
        results[i] = result;
    }
    for(int i = 0;i < m;i++) {
        printf("%lld\n",results[i]);
    }
    return 0;
}
