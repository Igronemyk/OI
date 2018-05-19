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

    void insert(int *keys) {
        int newNodeSign = newNode(keys);
        insert(root,newNodeSign,0);
    }

    void insert(int &now,const int &newNodeSign,int nowK) {
        if(now == 0) {
            now = newNodeSign;
            return;
        }
        D = nowK;
        bool r1 = comp(now,newNodeSign),r2 = comp(newNodeSign,now);
        if(r1 && r2) {
            kdSize--;
        }else if(r1) {
            insert(kn[now].ch[1],newNodeSign,nowK ^ 1);
        }else {
            insert(kn[now].ch[0],newNodeSign,nowK ^ 1);
        }
        updateInfo(now);
    }

    int guessValue(int now) {
        if(now == 0) return INF;
        int result = 0;
        result += max(0,kn[now].minKey[0] - nowX);
        result += max(0,nowX - kn[now].maxKey[0]);
        result += max(0,kn[now].minKey[1] - nowY);
        result += max(0,nowY - kn[now].maxKey[1]);
        return result;
    }

    int query(int x,int y) {
        nowAns = INF;
        nowX = x;
        nowY = y;
        query(root);
        return nowAns;
    }

    void query(int now) {
        if(now == 0) return;
        nowAns = min(nowAns,getDis(nowX,nowY,kn[now].key[0],kn[now].key[1]));
        int dl = guessValue(kn[now].ch[0]),dr = guessValue(kn[now].ch[1]);
        if(dl < dr) {
            if(dl < nowAns) {
                query(kn[now].ch[0]);
            }
            if(dr < nowAns) {
                query(kn[now].ch[1]);
            }
        }else {
            if(dr < nowAns) {
                query(kn[now].ch[1]);
            }
            if(dl < nowAns) {
                query(kn[now].ch[0]);
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
    int N = read<int>(),M = read<int>();
    Data *datas = new Data[N];
    for(int i = 0;i < N;i++) {
        int x = read<int>(),y = read<int>();
        datas[i] = make_pair(x,y);
    }
    KDTree tree(datas,N);
    int *keys = new int[K];
    while(M--) {
        int t = read<int>();
        keys[0] = read<int>();
        keys[1] = read<int>();
        if(t == 1) {
            tree.insert(keys);
        }else {
            printf("%d\n",tree.query(keys[0],keys[1]));
        }
    }
    return 0;
}
