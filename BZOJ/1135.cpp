#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 1e6;
const long long INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2];
    long long leftMaxValue,rightMaxValue,maxValue,sumValue;

    SegmentNode() : leftMaxValue(-INF) , rightMaxValue(-INF) , maxValue(-INF) ,sumValue(0) {
        ch[0] = ch[1] = 0;
    }

    SegmentNode(long long value) : leftMaxValue(value) , rightMaxValue(value) , maxValue(value) , sumValue(value) {
        ch[0] = ch[1] = 0;
    }

} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0,n,m,k,d;

struct SegmentTree {
    int root,left,right;

    SegmentTree(int left,int right) : root(buildTree(left,right)) , left(left) , right(right) { }

    int newNode() {
        sn[++segmentSize] = SegmentNode();
        return segmentSize;
    }

    int newNode(long long value) {
        sn[++segmentSize] = SegmentNode(value);
        return segmentSize;
    }

    int buildTree(int left,int right) {
        if(left == right) return newNode(-k);
        int mid = (left + right) >> 1,now = newNode();
        sn[now].ch[0] = buildTree(left,mid);
        sn[now].ch[1] = buildTree(mid + 1,right);
        updateInfo(now);
        return now;
    }

    void updateInfo(int now) {
        sn[now].leftMaxValue = max(sn[sn[now].ch[0]].leftMaxValue,sn[sn[now].ch[0]].sumValue + sn[sn[now].ch[1]].leftMaxValue);
        sn[now].rightMaxValue = max(sn[sn[now].ch[1]].rightMaxValue,sn[sn[now].ch[1]].sumValue + sn[sn[now].ch[0]].rightMaxValue);
        sn[now].maxValue = max(sn[sn[now].ch[0]].rightMaxValue + sn[sn[now].ch[1]].leftMaxValue,max(sn[sn[now].ch[0]].maxValue,sn[sn[now].ch[1]].maxValue));
        sn[now].sumValue = sn[sn[now].ch[0]].sumValue + sn[sn[now].ch[1]].sumValue;
    }

    void update(int pos,int value) {
        update(root,left,right,pos,value);
    }

    void update(int now,int left,int right,int pos,int value) {
        if(left == right) {
            long long newValue = sn[now].sumValue + value;
            sn[now] = SegmentNode(newValue);
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            update(sn[now].ch[0],left,mid,pos,value);
        }else {
            update(sn[now].ch[1],mid + 1,right,pos,value);
        }
        updateInfo(now);
    }

    long long getMaxValue() {
        return sn[root].maxValue;
    }

};

int main() {
    n = read<int>(); m = read<int>(); k = read<int>(); d = read<int>();
    long long checkResult = k * 1LL * d;
    SegmentTree stree(1,n);
    while(m--) {
        int sign = read<int>(),cnt = read<int>();
        stree.update(sign,cnt);
        if(stree.getMaxValue() <= checkResult) {
            printf("TAK\n");
        }else {
            printf("NIE\n");
        }
    }
    return 0;
}
