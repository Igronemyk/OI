#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int K = 2;
const int INF = 0x3f3f3f3f;
const int MAX_KDNODE_SIZE = 50010;
const int MAXN = 50010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct KDNode {
    int ch[2],minKey[K],maxKey[K],key[K],value;
    long long sumValue;

    KDNode() : value(0) , sumValue(0) {
        for(int i = 0;i < K;i++) minKey[i] = INF;
        for(int i = 0;i < K;i++) maxKey[i] = -INF;
        for(int i = 0;i < K;i++) key[i] = 0;
        ch[0] = 0;
        ch[1] = 0;
    }

    KDNode(int *keys,int value) : value(value) , sumValue(value) {
        for(int i = 0;i < K;i++) {
            minKey[i] = keys[i];
            maxKey[i] = keys[i];
            key[i] = keys[i];
        }
        ch[0] = 0;
        ch[1] = 0;
    }
} kn[MAX_KDNODE_SIZE];

int kdSize = 0,travelPos[MAX_KDNODE_SIZE],travelCnt;

struct Comparator {
    int now;

    Comparator() : now(0) { }

    Comparator(int now) : now(now) { }

    bool operator () (const int &a,const int &b) const {
        if(kn[a].key[now] != kn[b].key[now]) return kn[a].key[now] < kn[b].key[now];
        return kn[a].key[now ^ 1] < kn[b].key[now ^ 1];
    }
} comp[K];

struct Data {
    int key[K];
    int value;

    Data() : value(-1) { }

    Data(int *keys,int value) : value(value) {
        for(int i = 0;i < K;i++) key[i] = keys[i];
    }
} datas[MAXN];

long long nowA,nowB,nowC;

struct KDTree {
    int root;

    KDTree() : root(0) { }

    KDTree(Data *datas,int size) : root(build(datas,size)) { }

    void updateInfo(int now) {
        for(int i = 0;i < K;i++) {
            kn[now].minKey[i] = min(kn[now].key[i],min(kn[kn[now].ch[0]].minKey[i],kn[kn[now].ch[1]].minKey[i]));
            kn[now].maxKey[i] = max(kn[now].key[i],max(kn[kn[now].ch[0]].maxKey[i],kn[kn[now].ch[1]].maxKey[i]));
        }
        kn[now].sumValue = kn[now].value + kn[kn[now].ch[0]].sumValue + kn[kn[now].ch[1]].sumValue;
    }

    int newNode(int *keys,int value) {
        kn[++kdSize] = KDNode(keys,value);
        return kdSize;
    }

    int build(Data *datas,int size) {
        for(int i = 0;i < size;i++) {
            Data &tmpData = datas[i];
            travelPos[travelCnt++] = newNode(tmpData.key,tmpData.value);
        }
        int result = buildTree(0,size - 1,0);
        travelCnt = 0;
        return result;
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

    long long query(long long a,long long b,long long c) {
        nowA = a;
        nowB = b;
        nowC = c;
        return query(root);
    }

    bool check(long long x,long long y) {
        return nowA * x + nowB * y < nowC;
    }

    int check(int now) {
        if(now == 0) return 0;
        return check(kn[now].minKey[0],kn[now].minKey[1]) + check(kn[now].maxKey[0],kn[now].maxKey[1]) + check(kn[now].minKey[0],kn[now].maxKey[1]) + check(kn[now].maxKey[0],kn[now].minKey[1]);
    }


    long long query(int now) {
        if(now == 0) return 0;
        long long result = 0;
        if(check(kn[now].key[0],kn[now].key[1])) result += kn[now].value;
        int resultL = check(kn[now].ch[0]),resultR = check(kn[now].ch[1]);
        if(resultL == 4) {
            result += kn[kn[now].ch[0]].sumValue;
        }else if(resultL > 0) {
            result += query(kn[now].ch[0]);
        }
        if(resultR == 4) {
            result += kn[kn[now].ch[1]].sumValue;
        }else if(resultR > 0) {
            result += query(kn[now].ch[1]);
        }
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
    int n = read<int>(),m = read<int>(),*keys = new int[K];
    for(int i = 0;i < n;i++) {
        keys[0] = read<int>();keys[1] = read<int>();
        int h = read<int>();
        datas[i] = Data(keys,h);
    }
    KDTree tree(datas,n);
    while(m--) {
        int a = read<int>(),b = read<int>(),c = read<int>();
        printf("%lld\n",tree.query(a,b,c));
    }
    return 0;
}
