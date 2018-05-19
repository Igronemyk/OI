#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 500010;
const int MAX_SEGMENT_NODE_SIZE =4e6;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SegmentNode {
    int ch[2],maxValue,addTag;

    SegmentNode() : maxValue(0) , addTag(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SEGMENT_NODE_SIZE];

int segmentSize = 0;

struct SegmentTree {
    int root,left,right;

    SegmentTree() : root(0) , left(0) , right(0) {}

    SegmentTree(int left,int right) : root(buildTree(left,right)) , left(left) , right(right) { }

    int newNode() {
        sn[++segmentSize] = SegmentNode();
        return segmentSize;
    }

    void updateInfo(int now) {
        sn[now].maxValue = max(sn[sn[now].ch[0]].maxValue,sn[sn[now].ch[1]].maxValue) + sn[now].addTag;
    }

    int buildTree(int left,int right) {
        if(left == right) return newNode();
        int now = newNode(),mid = (left + right) >> 1;
        sn[now].ch[0] = buildTree(left,mid);
        sn[now].ch[1] = buildTree(mid + 1,right);
        updateInfo(now);
        return now;
    }

    void update(int l,int r,int value) {
        update(root,left,right,l,r,value);
    }

    void update(int now,int left,int right,int l,int r,int value) {
        if(left == l && right == r) {
            sn[now].addTag += value;
            updateInfo(now);
            return;
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                update(sn[now].ch[0],left,mid,l,r,value);
            }else {
                update(sn[now].ch[0],left,mid,l,mid,value);
                update(sn[now].ch[1],mid + 1,right,mid + 1,r,value);
            }
        }else {
            update(sn[now].ch[1],mid + 1,right,l,r,value);
        }
        updateInfo(now);
    }

    int getMaxValue() {
        return sn[root].maxValue;
    }

};

typedef pair<pair<int,int>,int> Info;

Info infos[MAXN];

int sortedValues[MAXN * 2];

bool comp(const Info &a,const Info &b) {
    return a.second < b.second;
}

int main() {
    int N = read<int>(),M = read<int>();
    int nowIndex = 0;
    for(int i = 0;i < N;i++) {
        int left = read<int>(),right = read<int>();
        infos[i] = make_pair(make_pair(left,right),right - left + 1);
        sortedValues[nowIndex++] = left;
        sortedValues[nowIndex++] = right;
    }
    sort(sortedValues,sortedValues + nowIndex);
    int sortedSize = unique(sortedValues,sortedValues + nowIndex) - sortedValues;
    SegmentTree stree(0,sortedSize - 1);
    for(int i = 0;i < N;i++) {
        int left = infos[i].first.first,right = infos[i].first.second;
        left = lower_bound(sortedValues,sortedValues + sortedSize,left) - sortedValues;
        right = lower_bound(sortedValues,sortedValues + sortedSize,right) - sortedValues;
        infos[i].first = make_pair(left,right);
    }
    sort(infos,infos + N,comp);
    int nowLeftSign = 0,minResult = INF;
    for(int i = 0;i < N;i++) {
        Info &tmpInfo = infos[i];
        stree.update(tmpInfo.first.first,tmpInfo.first.second,1);
        while(stree.getMaxValue() >= M) {
            Info &tmpInfo1 = infos[nowLeftSign];
            minResult = min(minResult,tmpInfo.second - tmpInfo1.second);
            stree.update(tmpInfo1.first.first,tmpInfo1.first.second,-1);
            nowLeftSign++;
        }
    }
    if(minResult == INF) {
        printf("%d\n",-1);
    }else {
        printf("%d\n",minResult);
    }
    return 0;
}
