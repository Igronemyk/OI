#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_SEGMET_NODE_SIZE = 5e6;
const int BUFFER_SIZE = 4;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2],leftValue,rightValue,sumValue;

    SegmentNode() : leftValue(0) , rightValue(0) , sumValue(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SEGMET_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root,left,right;

    static int newNode() {
        return copyNode(0);
    }

    static int copyNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    void updateInfo(int now) {
        sn[now].leftValue = max(sn[sn[now].ch[0]].leftValue,sn[sn[now].ch[0]].sumValue + sn[sn[now].ch[1]].leftValue);
        sn[now].rightValue = max(sn[sn[now].ch[1]].rightValue,sn[sn[now].ch[1]].sumValue + sn[sn[now].ch[0]].rightValue);
        sn[now].sumValue = sn[sn[now].ch[0]].sumValue + sn[sn[now].ch[1]].sumValue;
    }

    SegmentTree() : root(0) , left(-1) , right(-1) { }

    SegmentTree(int n) : left(0) , right(n - 1) {
        root = build(0,n - 1);
    }

    int build(int left,int right) {
        int now = newNode();
        if(left == right) {
            sn[now].leftValue = 1;
            sn[now].rightValue = 1;
            sn[now].sumValue = 1;
            return now;
        }
        int mid = (left + right) >> 1;
        sn[now].ch[0] = build(left,mid);
        sn[now].ch[1] = build(mid + 1,right);
        updateInfo(now);
        return now;
    }

    SegmentTree(int root,int left,int right) : root(root) , left(left) , right(right) { }

    void update(int pos,int value) {
        update(root,left,right,pos,value);
    }

    void update(int now,int left,int right,int pos,int value) {
        if(left == right) {
            sn[now].leftValue = value;
            sn[now].rightValue = value;
            sn[now].sumValue = value;
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = copyNode(sn[now].ch[0]);
            update(sn[now].ch[0],left,mid,pos,value);
        }else {
            sn[now].ch[1] = copyNode(sn[now].ch[1]);
            update(sn[now].ch[1],mid + 1,right,pos,value);
        }
        updateInfo(now);
    }

    int querySum(int l,int r) {
        return querySum(root,left,right,l,r);
    }

    int querySum(int now,int left,int right,int l,int r) {
        if(left == l && right == r) {
            return sn[now].sumValue;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return querySum(sn[now].ch[0],left,mid,l,r);
            }else {
                return querySum(sn[now].ch[0],left,mid,l,mid) + querySum(sn[now].ch[1],mid + 1,right,mid + 1,r);
            }
        }else {
            return querySum(sn[now].ch[1],mid + 1,right,l,r);
        }
    }

    int queryLeftValue(int l,int r) {
        return queryLeftValue(root,left,right,l,r);
    }

    int queryLeftValue(int now,int left,int right,int l,int r) {
        if(left == l && right == r) {
            return sn[now].leftValue;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return queryLeftValue(sn[now].ch[0],left,mid,l,r);
            }else {
                return max(queryLeftValue(sn[now].ch[0],left,mid,l,mid),querySum(sn[now].ch[0],left,mid,l,mid) + queryLeftValue(sn[now].ch[1],mid + 1,right,mid + 1,r));
            }
        }else {
            return queryLeftValue(sn[now].ch[1],mid + 1,right,l,r);
        }
    }

    int queryRightValue(int l,int r) {
        return queryRightValue(root,left,right,l,r);
    }

    int queryRightValue(int now,int left,int right,int l,int r) {
        if(left == l && right == r) {
            return sn[now].rightValue;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return queryRightValue(sn[now].ch[0],left,mid,l,r);
            }else {
                return max(queryRightValue(sn[now].ch[1],mid + 1,right,mid + 1,r),querySum(sn[now].ch[1],mid + 1,right,mid + 1,r) + queryRightValue(sn[now].ch[0],left,mid,l,mid));
            }
        }else {
            return queryRightValue(sn[now].ch[1],mid + 1,right,l,r);
        }
    }

    SegmentTree copy() {
        return SegmentTree(copyNode(root),left,right);
    }
};

bool check(SegmentTree &stree,int a,int b,int c,int d) {
    int result = 0;
    if(b + 1 <= c - 1) {
        result += stree.querySum(b + 1,c - 1);
    }
    result += stree.queryRightValue(a,b);
    result += stree.queryLeftValue(c,d);
    return result >= 0;

}

int main() {
    int n = read<int>();
    pair<int,int> *values = new pair<int,int>[n];
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        values[i] = make_pair(tmpValue,i);
    }
    sort(values,values + n);
    SegmentTree *strees = new SegmentTree[n];
    strees[0] = SegmentTree(n);
    for(int i = 1;i < n;i++) {
        strees[i] = strees[i - 1].copy();
        strees[i].update(values[i - 1].second,-1);
    }
    int lastAns = 0,Q = read<int>(),*tmp = new int[BUFFER_SIZE];
    while(Q--) {
        for(int i = 0;i < BUFFER_SIZE;i++) {
            tmp[i] = ((read<int>() + lastAns) % n);
        }
        sort(tmp,tmp + BUFFER_SIZE);
        int left = 0,right = n - 1,ans = 0;
        while(left <= right) {
            int mid = (left + right) >> 1;
            if(check(strees[mid],tmp[0],tmp[1],tmp[2],tmp[3])) {
                left = mid + 1;
                ans = max(ans,mid);
            }else {
                right = mid - 1;
            }
        }
        printf("%d\n",values[ans].first);
        lastAns = values[ans].first;
    }
}
