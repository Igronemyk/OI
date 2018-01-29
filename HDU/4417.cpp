#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 3400010;
const int MAXN = 100010;
int MIN_VAL_RANGE = 0;
int MAX_VAL_RANGE = 1000000000;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2],cnt;
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root;

    static int newNode() {
        ++segmentSize;
        sn[segmentSize].ch[0] = 0;
        sn[segmentSize].ch[1] = 0;
        sn[segmentSize].cnt = 0;
        return segmentSize;
    }

    static int newNode(int nodeSign) {
        ++segmentSize;
        sn[segmentSize].ch[0] = sn[nodeSign].ch[0];
        sn[segmentSize].ch[1] = sn[nodeSign].ch[1];
        sn[segmentSize].cnt = sn[nodeSign].cnt;
        return segmentSize;
    }

    void insert(int pos) {
        insert(root,MIN_VAL_RANGE,MAX_VAL_RANGE,pos);
    }

    void insert(int now,int left,int right,int pos) {
        sn[now].cnt++;
        if(left == right) return;
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = newNode(sn[now].ch[0]);
            insert(sn[now].ch[0],left,mid,pos);
        }else {
            sn[now].ch[1] = newNode(sn[now].ch[1]);
            insert(sn[now].ch[1],mid + 1,right,pos);
        }
    }

    static int queryCnt(int r,int l,int nowLeft,int nowRight,int left,int right) {
        if(nowLeft == left && nowRight == right) {
            return sn[r].cnt - sn[l].cnt;
        }
        int mid = (nowLeft + nowRight) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                return queryCnt(sn[r].ch[0],sn[l].ch[0],nowLeft,mid,left,right);
            }else {
                return queryCnt(sn[r].ch[0],sn[l].ch[0],nowLeft,mid,left,mid) + queryCnt(sn[r].ch[1],sn[l].ch[1],mid + 1,nowRight,mid + 1,right);
            }
        }else {
            return queryCnt(sn[r].ch[1],sn[l].ch[1],mid + 1,nowRight,left,right);
        }
    }
};

SegmentTree strees[MAXN];
int values[MAXN],sortedValues[MAXN * 2],qL[MAXN],qR[MAXN],qH[MAXN];

int main() {
    sn[0].ch[0] = 0;
    sn[0].ch[1] = 0;
    sn[0].cnt = 0;
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        printf("Case %d:\n",nowCase);
        segmentSize = 0;
        int n = read<int>(),m = read<int>();
        for(int i = 0;i < n;i++) {
            values[i] = read<int>();
            sortedValues[i] = values[i];
        }
        for(int i = 0;i < m;i++) {
            qL[i] = read<int>();
            qR[i] = read<int>();
            qH[i] = read<int>();
            qL[i]++;
            qR[i]++;
            sortedValues[i + n] = qH[i];
        }
        sort(sortedValues,sortedValues + n + m);
        int sortedSize = unique(sortedValues,sortedValues + n + m) - sortedValues;
        MAX_VAL_RANGE = sortedSize - 1;
        strees[0].root = SegmentTree::newNode();
        for(int i = 0;i < n;i++) {
            strees[i + 1].root = SegmentTree::newNode(strees[i].root);
            strees[i + 1].insert(lower_bound(sortedValues,sortedValues + sortedSize,values[i]) - sortedValues);
        }
        for(int i = 0;i < m;i++) {
            printf("%d\n",SegmentTree::queryCnt(strees[qR[i]].root,strees[qL[i] - 1].root,MIN_VAL_RANGE,MAX_VAL_RANGE,MIN_VAL_RANGE,lower_bound(sortedValues,sortedValues + sortedSize,qH[i]) - sortedValues));
        }
    }
    return 0;
}
