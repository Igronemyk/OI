#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 2600000;
const int MAX_SEGMENT_NODE_SIZE = 2600000;
const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 1e8;
const int MAXN = 50010;
const int INF = 2147483647;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,priority,size;

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
    int root;

    typedef pair<int,int> DRoot;

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

    int getCnt(int left,int right) {
        int leftCount = lowerCount(left),rightCount = lowerCount(right + 1);
        return rightCount - leftCount;
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
    int ch[2],left,right;
    Treap treap;

    SegmentNode() : left(left) , right(right) {
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

    SegmentTree(int left,int right) {
        root = newNode(left,right);
    }

    void insert(int pos,int val) {
        insert(root,pos,val);
    }

    void insert(int now,int pos,int val) {
        sn[now].treap.insert(val);
        if(sn[now].isLeafNode()) return;
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(pos <= mid) {
            if(sn[now].ch[0] == 0) {
                sn[now].ch[0] = newNode(sn[now].left,mid);
            }
            insert(sn[now].ch[0],pos,val);
        }else {
            if(sn[now].ch[1] == 0) {
                sn[now].ch[1] = newNode(mid + 1,sn[now].right);
            }
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

    int queryLessThan(int left,int right,int value) {
        return queryCnt(root,0,value - 1,left,right);
    }

    int queryNotGreaterThan(int left,int right,int value) {
        return queryCnt(root,0,value,left,right);
    }

    int queryCnt(int now,int left,int right,int queryLeft,int queryRight) {
        if(now == 0) return 0;
        if(sn[now].left == left && sn[now].right == right) {
            int tmpResult = sn[now].treap.getCnt(queryLeft,queryRight);
            return tmpResult;
        }
        int mid = (sn[now].left + sn[now].right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryCnt(sn[now].ch[0],left,right,queryLeft,queryRight);
            }else {
                return queryCnt(sn[now].ch[0],left,mid,queryLeft,queryRight) + queryCnt(sn[now].ch[1],mid + 1,right,queryLeft,queryRight);
            }
        }else {
            return queryCnt(sn[now].ch[1],left,right,queryLeft,queryRight);
        }
    }

    int queryValue(int left,int right,int rank) {
        return queryValue(root,left,right,rank);
    }

    int queryValue(int now,int left,int right,int rank) {
        if(sn[now].isLeafNode()) {
            return sn[now].left;
        }
        int cnt = sn[sn[now].ch[0]].treap.getCnt(left,right);
        if(cnt < rank) {
            return queryValue(sn[now].ch[1],left,right,rank - cnt);
        }else {
            return queryValue(sn[now].ch[0],left,right,rank);
        }
    }

    int queryPrecursor(int left,int right,int value) {
        int cnt = queryLessThan(left,right,value);
        if(cnt == 0) return -INF;
        return queryValue(left,right,cnt);
    }

    int querySuccessor(int left,int right,int value) {
        int cnt = queryNotGreaterThan(left,right,value);
        if(cnt + 1 > right - left + 1) {
            return INF;
        }
        int tmpValue = queryValue(left,right,cnt + 1);
        if(tmpValue == value) {
            if(cnt + 1 == right - left + 1) return INF;
            return queryValue(left,right,cnt + 2);
        }else {
            return queryValue(left,right,cnt + 1);
        }
    }
};

int values[MAXN];

int main() {
    srand(123456);
    int n = read<int>(),m = read<int>();
    SegmentTree stree(MIN_VAL_RANGE,MAX_VAL_RANGE);
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        stree.insert(values[i],i);
    }
    while(m--) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",stree.queryLessThan(l,r,k) + 1);
                break;
            }
            case 2: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",stree.queryValue(l,r,k));
                break;
            }
            case 3: {
                int pos = read<int>(),k = read<int>();
                pos--;
                stree.remove(values[pos],pos);
                values[pos] = k;
                stree.insert(values[pos],pos);
                break;
            }
            case 4: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",stree.queryPrecursor(l,r,k));
                break;
            }
            case 5: {
                int l = read<int>(),r = read<int>(),k = read<int>();
                l--; r--;
                printf("%d\n",stree.querySuccessor(l,r,k));
                break;
            }
        }
    }
    return 0;
}
