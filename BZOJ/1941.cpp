#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int K = 2;
const int INF = 0x3f3f3f3f;
const int MAX_KDNODE_SIZE = 1e6 + 10;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct KDNode {
    int ch[2],key[K],minKey[K],maxKey[K];

    KDNode() {
        for(int i = 0;i < K;i++) {
            minKey[i] = INF;
            maxKey[i] = -INF;
            key[i] = 0;
        }
        ch[0] = 0;
        ch[1] = 0;
    }

    KDNode(int *keys) {
        for(int i = 0;i < K;i++) {
            minKey[i] = keys[i];
            maxKey[i] = keys[i];
            key[i] = keys[i];
        }
        ch[0] = 0;
        ch[1] = 0;
    }
} kn[MAX_KDNODE_SIZE];

int kdSize,travelPos[MAX_KDNODE_SIZE],travelCnt,D;

typedef pair<int,int> Data;

bool comp(int a,int b) {
    if(kn[a].key[D] != kn[b].key[D]) return kn[a].key[D] < kn[b].key[D];
    return kn[a].key[D ^ 1] < kn[b].key[D ^ 1];
}

int getDis(int x1,int y1,int x2,int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int nowX,nowY,nowAns;

struct KDTree {
    int root;

    KDTree() : root(0) { }

    KDTree(Data *datas,int size) : root(build(datas,size)) { }

    int newNode(int *keys) {
        kn[++kdSize] = KDNode(keys);
        return kdSize;
    }

    void updateInfo(int now) {
        for(int i = 0; i < K;i++) {
            kn[now].minKey[i] = min(kn[now].key[i],min(kn[kn[now].ch[0]].minKey[i],kn[kn[now].ch[1]].minKey[i]));
            kn[now].maxKey[i] = max(kn[now].key[i],max(kn[kn[now].ch[0]].maxKey[i],kn[kn[now].ch[1]].maxKey[i]));
        }
    }

    int guessMinValue(int now) {
        if(now == 0) return INF;
        int result = 0;
        result += max(0,kn[now].minKey[0] - nowX);
        result += max(0,nowX - kn[now].maxKey[0]);
        result += max(0,kn[now].minKey[1] - nowY);
        result += max(0,nowY - kn[now].maxKey[1]);
        return result;
    }

    int queryMin(int x,int y) {
        nowAns = INF;
        nowX = x;
        nowY = y;
        queryMin(root);
        return nowAns;
    }

    void queryMin(int now) {
        if(now == 0) return;
        if(!(kn[now].key[0] == nowX && kn[now].key[1] == nowY)) {
            nowAns = min(nowAns,getDis(nowX,nowY,kn[now].key[0],kn[now].key[1]));
        }
        int dl = guessMinValue(kn[now].ch[0]),dr = guessMinValue(kn[now].ch[1]);
        if(dl < dr) {
            if(dl < nowAns) {
                queryMin(kn[now].ch[0]);
            }
            if(dr < nowAns) {
                queryMin(kn[now].ch[1]);
            }
        }else {
            if(dr < nowAns) {
                queryMin(kn[now].ch[1]);
            }
            if(dl < nowAns) {
                queryMin(kn[now].ch[0]);
            }
        }
    }

    int guessMaxValue(int now) {
        if(now == 0) return -INF;
        return max(abs(kn[now].minKey[0] - nowX),abs(kn[now].maxKey[0] - nowX)) + max(abs(kn[now].minKey[1] - nowY),abs(kn[now].maxKey[1] - nowY));
    }

    int queryMax(int x,int y) {
        nowAns = 0;
        nowX = x;
        nowY = y;
        queryMax(root);
        return nowAns;
    }

    void queryMax(int now) {
        if(now == 0) return;
        if(!(kn[now].key[0] == nowX && kn[now].key[1] == nowY)) {
            nowAns = max(nowAns,getDis(nowX,nowY,kn[now].key[0],kn[now].key[1]));
        }
        int dl = guessMaxValue(kn[now].ch[0]),dr = guessMaxValue(kn[now].ch[1]);
        if(dl > dr) {
            if(dl > nowAns) {
                queryMax(kn[now].ch[0]);
            }
            if(dr > nowAns) {
                queryMax(kn[now].ch[1]);
            }
        }else {
            if(dr > nowAns) {
                queryMax(kn[now].ch[1]);
            }
            if(dl > nowAns) {
                queryMax(kn[now].ch[0]);
            }
        }
    }

    int build(Data *datas,int size) {
        int *keys = new int[K];
        for(int i = 0;i < size;i++) {
            keys[0] = datas[i].first;
            keys[1] = datas[i].second;
            travelPos[travelCnt++] = newNode(keys);
        }
        int result = buildTree(0,travelCnt - 1,0);
        travelCnt = 0;
        return result;
    }

    int buildTree(int left,int right,int nowK) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        D = nowK;
        nth_element(travelPos + left,travelPos + mid,travelPos + right + 1,comp);
        int now = travelPos[mid];
        kn[now].ch[0] = buildTree(left,mid - 1,nowK ^ 1);
        kn[now].ch[1] = buildTree(mid + 1,right,nowK ^ 1);
        updateInfo(now);
        return now;
    }
};

int main() {
    int N = read<int>();
    Data *datas = new Data[N];
    for(int i = 0;i < N;i++) {
        int x = read<int>(),y = read<int>();
        datas[i] = make_pair(x,y);
    }
    KDTree tree(datas,N);
    int minDelta = INF;
    for(int i = 0;i < N;i++) {
        Data &tmpData = datas[i];
        int maxValue = tree.queryMax(tmpData.first,tmpData.second),minValue = tree.queryMin(tmpData.first,tmpData.second);
        if(maxValue - minValue < minDelta) {
            minDelta = maxValue - minValue;
        }
    }
    printf("%d\n",minDelta);
    return 0;
}
