#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MIN_VAL_RANGE = 1;
const int MAX_VAL_RANGE = 1e7;
const int MAX_SEGMENT_NODE_SIZE = 1e6;
const int MAXN = 10010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2];
    bool tag;
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root,left,right;

    static int newNode() {
        ++segmentSize;
        sn[segmentSize].ch[0] = 0;
        sn[segmentSize].ch[1] = 0;
        sn[segmentSize].tag = 0;
        return segmentSize;
    }

    SegmentTree(int left,int right) : left(left) , right(right) {
        root = newNode();
        build(root,left,right);
    }

    void build(int now,int left,int right) {
        if(left == right) return;
        int mid = (left + right) >> 1;
        sn[now].ch[0] = newNode();
        build(sn[now].ch[0],left,mid);
        sn[now].ch[1] = newNode();
        build(sn[now].ch[1],mid + 1,right);
    }

    void update(int l,int r) {
        update(root,left,right,l,r);
    }

    void updateInfo(int now) {
        if(sn[sn[now].ch[0]].tag && sn[sn[now].ch[1]].tag) {
            sn[now].tag = true;
        }
    }

    void update(int now,int left,int right,int l,int r) {
        if(sn[now].tag) return;
        if(left == l && right == r) {
            sn[now].tag = true;
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                update(sn[now].ch[0],left,mid,l,r);
            }else {
                update(sn[now].ch[0],left,mid,l,mid);
                update(sn[now].ch[1],mid + 1,right,mid + 1,r);
            }
        }else {
            update(sn[now].ch[1],mid + 1,right,l,r);
        }
        updateInfo(now);
    }

    bool check(int l,int r) {
        return check(root,left,right,l,r);
    }

    bool check(int now,int left,int right,int l,int r) {
        if(sn[now].tag) return false;
        if(left == l && right == r) {
            return true;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return check(sn[now].ch[0],left,mid,l,r);
            }else {
                return check(sn[now].ch[0],left,mid,l,mid) || check(sn[now].ch[1],mid + 1,right,mid + 1,r);
            }
        }else {
            return check(sn[now].ch[1],mid + 1,right,l,r);
        }
    }
};

pair<int,int> values[MAXN];
int sortedValues[MAXN * 2];

int main() {
    int T = read<int>();
    while(T--) {
        segmentSize = 0;
        int n = read<int>(),sortedSize = 0;
        for(int i = 0;i < n;i++) {
            values[i].first = read<int>();
            values[i].second = read<int>();
            sortedValues[sortedSize++] = values[i].first;
            sortedValues[sortedSize++] = values[i].second;
        }
        sort(sortedValues,sortedValues + sortedSize);
        sortedSize = unique(sortedValues,sortedValues + sortedSize) - sortedValues;
        SegmentTree stree(0,sortedSize - 1);
        int result = 0;
        for(int i = n - 1;i >= 0;i--) {
            int left = lower_bound(sortedValues,sortedValues + sortedSize,values[i].first) - sortedValues,right = lower_bound(sortedValues,sortedValues + sortedSize,values[i].second) - sortedValues;
            if(stree.check(left,right)) {
                result++;
            }
            stree.update(left,right);
        }
        printf("%d\n",result);
    }
    return 0;
}
