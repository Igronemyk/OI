#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MIN_VAL_RANGE = 1;
const int MAX_VAL_RANGE = 10000;
const int MAX_SEGMENT_NODE_SIZE = 5000010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2],cnt;

    SegmentNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root;

    static int newNode() {
        return copyNode(0);
    }

    static int copyNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    SegmentTree() : root(newNode()) { }

    SegmentTree(int root) : root(root) { }

    void updateInfo(int now) {
        sn[now].cnt = sn[sn[now].ch[0]].cnt + sn[sn[now].ch[1]].cnt;
    }

    void insert(int value) {
        insert(root,MIN_VAL_RANGE,MAX_VAL_RANGE,value);
    }

    void insert(int now,int left,int right,int value) {
        if(left == right) {
            sn[now].cnt++;
            return;
        }
        int mid = (left + right) >> 1;
        if(value <= mid) {
            sn[now].ch[0] = copyNode(sn[now].ch[0]);
            insert(sn[now].ch[0],left,mid,value);
        }else {
            sn[now].ch[1] = copyNode(sn[now].ch[1]);
            insert(sn[now].ch[1],mid + 1,right,value);
        }
        updateInfo(now);
    }

    static int getMode(SegmentTree &l,SegmentTree &r,int k) {
        return getMode(l.root,r.root,MIN_VAL_RANGE,MAX_VAL_RANGE,k);
    }

    static int getMode(int l,int r,int left,int right,int k) {
        if(left == right) {
            if(sn[r].cnt - sn[l].cnt > k) {
                return left;
            }else {
                return 0;
            }
        }
        int mid = (left + right) >> 1;
        if(sn[sn[r].ch[0]].cnt - sn[sn[l].ch[0]].cnt > k) return getMode(sn[l].ch[0],sn[r].ch[0],left,mid,k);
        if(sn[sn[r].ch[1]].cnt - sn[sn[l].ch[1]].cnt > k) return getMode(sn[l].ch[1],sn[r].ch[1],mid + 1,right,k);
        return 0;
    }

    SegmentTree copy() {
        return SegmentTree(copyNode(root));
    }

};

int main() {
    int N = read<int>(),C = read<int>();
    SegmentTree *strees = new SegmentTree[N + 1];
    for(int i = 1;i <= N;i++) {
        strees[i] = strees[i - 1].copy();
        strees[i].insert(read<int>());
    }
    int M = read<int>();
    while(M--) {
        int left = read<int>(),right = read<int>();
        int result = SegmentTree::getMode(strees[left - 1],strees[right],(right - left + 1) / 2);
        if(result == 0) {
            printf("no\n");
        }else {
            printf("yes %d\n",result);
        }
    }
    return 0;
}
