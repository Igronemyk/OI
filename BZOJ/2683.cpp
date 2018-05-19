#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int K = 2;
const int INF = 0x3f3f3f3f;
const int MAX_KDNODE_SIZE = 200010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct KDNode {
    int ch[2],minKey[K],maxKey[K],key[K],value,size;
    long long sumValue;

    KDNode() : value(0) , size(0) , sumValue(0) {
        for(int i = 0;i < K;i++) minKey[i] = INF;
        for(int i = 0;i < K;i++) maxKey[i] = -INF;
        for(int i = 0;i < K;i++) key[i] = 0;
        ch[0] = 0;
        ch[1] = 0;
    }

    KDNode(int *keys,int value) : value(value) , size(1) , sumValue(value) {
        for(int i = 0;i < K;i++) minKey[i] = keys[i];
        for(int i = 0;i < K;i++) maxKey[i] = keys[i];
        for(int i = 0;i < K;i++) key[i] = keys[i];
        ch[0] = 0;
        ch[1] = 0;
    }

} kn[MAX_KDNODE_SIZE];

int kdSize = 0,travelPos[MAX_KDNODE_SIZE],travelCnt = 0;

struct Comparator {

    int now;

    Comparator() : now(0) { }

    Comparator(int now) : now(now) { }

    bool operator () (const int &a,const int &b) const {
        if(kn[a].key[now] != kn[b].key[now]) return kn[a].key[now] < kn[b].key[now];
        return kn[a].key[now ^ 1] < kn[b].key[now ^ 1];
    }
} comp[K];

struct KDTree {

    const static double alpha = 0.75;

    int root;

    KDTree() : root(0) { }

    int newNode(int *keys,int value) {
        kn[++kdSize] = KDNode(keys,value);
        return kdSize;
    }

    bool check(int now) {
        return (kn[kn[now].ch[0]].size > kn[now].size * alpha + 5) || (kn[kn[now].ch[1]].size > kn[now].size * alpha + 5);
    }

    void updateInfo(int now) {
        for(int i = 0;i < K;i++) {
            kn[now].minKey[i] = min(kn[now].key[i],min(kn[kn[now].ch[0]].minKey[i],kn[kn[now].ch[1]].minKey[i]));
            kn[now].maxKey[i] = max(kn[now].key[i],max(kn[kn[now].ch[0]].maxKey[i],kn[kn[now].ch[1]].maxKey[i]));
        }
        kn[now].size = kn[kn[now].ch[0]].size + kn[kn[now].ch[1]].size + 1;
        kn[now].sumValue = kn[kn[now].ch[0]].sumValue + kn[kn[now].ch[1]].sumValue + kn[now].value;
    }

    void travel(int now) {
        if(now == 0) return;
        travel(kn[now].ch[0]);
        travelPos[travelCnt++] = now;
        travel(kn[now].ch[1]);
    }

    int buildTree(int left,int right,int nowK) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        nth_element(travelPos + left,travelPos + mid,travelPos + right + 1,comp[nowK]);
        int now = travelPos[mid];
        kn[now].ch[0] = buildTree(left,mid - 1,nowK ^ 1);
        kn[now].ch[1] = buildTree(mid + 1,right,nowK ^ 1);
        updateInfo(now);
        return now;
    }

    void rebuild(int &now,int k) {
        travel(now);
        now = buildTree(0,travelCnt - 1,k);
        travelCnt = 0;
    }

    void insert(int *keys,int value) {
        int newNodeSign = newNode(keys,value);
        int *goat = NULL,goatK = -1;
        insert(root,0,newNodeSign,goat,goatK);
        if(goat != NULL) {
            rebuild(*goat,goatK);
        }
    }

    void insert(int &now,int nowK,int newNodeSign,int *&goat,int &goatK) {
        if(now == 0) {
            now = newNodeSign;
            return;
        }
        bool r1 = comp[nowK](now,newNodeSign),r2 = comp[nowK](newNodeSign,now);
        if(r1 && r2) {
            --kdSize;
            kn[now].value += kn[newNodeSign].value;
        }else if(r1) {
            insert(kn[now].ch[1],nowK ^ 1,newNodeSign,goat,goatK);
        }else {
            insert(kn[now].ch[0],nowK ^ 1,newNodeSign,goat,goatK);
        }
        updateInfo(now);
        if(check(now)) {
            goat = &now;
            goatK = nowK;
        }
    }

    bool inside(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
        return x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2;
    }

    bool outside(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
        return x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1;
    }

    long long getSumValue(int x1,int y1,int x2,int y2) {
        return getSumValue(root,x1,y1,x2,y2);
    }

    long long getSumValue(int now,int x1,int y1,int x2,int y2) {
        if(now == 0) return 0;
        if(inside(x1,y1,x2,y2,kn[now].minKey[0],kn[now].minKey[1],kn[now].maxKey[0],kn[now].maxKey[1])) return kn[now].sumValue;
        if(outside(x1,y1,x2,y2,kn[now].minKey[0],kn[now].minKey[1],kn[now].maxKey[0],kn[now].maxKey[1])) return 0;
        long long result = 0;
        if(inside(x1,y1,x2,y2,kn[now].key[0],kn[now].key[1],kn[now].key[0],kn[now].key[1])) result += kn[now].value;
        result += getSumValue(kn[now].ch[0],x1,y1,x2,y2);
        result += getSumValue(kn[now].ch[1],x1,y1,x2,y2);
        return result;
    }
};

void init() {
    for(int i = 0;i < K;i++) {
        comp[i] = Comparator(i);
    }
}
int main() {
    init();
    int N = read<int>();
    bool finish = false;
    KDTree tree;
    int *keys = new int[K];
    while(true) {
        if(finish) break;
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int x = read<int>(),y = read<int>(),A = read<int>();
                keys[0] = x;
                keys[1] = y;
                tree.insert(keys,A);
                break;
            }
            case 2: {
                int x1 = read<int>(),y1 = read<int>(),x2 = read<int>(),y2 = read<int>();
                printf("%lld\n",tree.getSumValue(x1,y1,x2,y2));
                break;
            }
            case 3: {
                finish = true;
                break;
            }
        }
    }
    return 0;
}
