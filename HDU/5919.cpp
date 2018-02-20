#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <climits>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 7200010;
const int MIN_VAL_RANGE = 1;
const int MAX_VAL_RANGE = 200010;
const int MAXN = 200010;

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
        return newNode(0);
    }

    static int newNode(int sign) {
        sn[++segmentSize] = sn[sign];
        return segmentSize;
    }

    SegmentTree() : root(newNode()) { }

    SegmentTree(int root) : root(newNode(root)) { }

    void update(int pos,int val) {
        update(root,MIN_VAL_RANGE,MAX_VAL_RANGE,pos,val);
    }

    void update(int now,int left,int right,int pos,int val) {
        sn[now].cnt += val;
        if(left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            sn[now].ch[0] = newNode(sn[now].ch[0]);
            update(sn[now].ch[0],left,mid,pos,val);
        }else {
            sn[now].ch[1] = newNode(sn[now].ch[1]);
            update(sn[now].ch[1],mid + 1,right,pos,val);
        }
    }

    int getCnt(int left,int right) {
        if(left > right) return 0;
        return getCnt(root,MIN_VAL_RANGE,MAX_VAL_RANGE,left,right);
    }

    int getCnt(int now,int left,int right,int l,int r) {
        if(now == 0) return 0;
        if(left == l && right == r) {
            return sn[now].cnt;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return getCnt(sn[now].ch[0],left,mid,l,r);
            }else {
                return getCnt(sn[now].ch[0],left,mid,l,mid) + getCnt(sn[now].ch[1],mid + 1,right,mid + 1,r);
            }
        }else {
            return getCnt(sn[now].ch[1],mid + 1,right,l,r);
        }
    }

    int getKth(int left,int right,int k) {
        int preCnt = getCnt(MIN_VAL_RANGE,left - 1);
        return getKth(root,MIN_VAL_RANGE,MAX_VAL_RANGE,k + preCnt);
    }

    int getKth(int now,int left,int right,int k) {
        if(left == right) {
            return left;
        }
        int cnt = sn[sn[now].ch[0]].cnt,mid = (left + right) >> 1;
        if(cnt < k) {
            return getKth(sn[now].ch[1],mid + 1,right,k - cnt);
        }else {
            return getKth(sn[now].ch[0],left,mid,k);
        }
    }

    SegmentTree copy() {
        return SegmentTree(root);
    }

};


SegmentTree strees[MAXN];
int nowPos[MAX_VAL_RANGE],values[MAXN];


int main() {
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        segmentSize = 0;
        memset(nowPos,0,sizeof(nowPos));
        int n = read<int>(),m = read<int>();
        for(int i = 1;i <= n;i++) {
            values[i] = read<int>();
        }
        strees[n + 1] = SegmentTree();
        for(int i = n;i >= 1;i--) {
            strees[i] = strees[i + 1].copy();
            int tmpValue = values[i],oldValue = nowPos[tmpValue];
            if(oldValue != 0) {
                strees[i].update(oldValue,-1);
            }
            strees[i].update(i,1);
            nowPos[tmpValue] = i;
        }
        int lastAns = 0;
        printf("Case #%d: ",nowCase);
        for(int i = 1;i <= m;i++) {
            int left = (read<int>() + lastAns) % n + 1,right = (read<int>() + lastAns) % n + 1;
            if(left > right) swap(left,right);
            int cnt = strees[left].getCnt(left,right);
            cnt = (cnt + 1) / 2;
            lastAns = strees[left].getKth(left,right,cnt);
            printf("%d",lastAns);
            if(i != m) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
