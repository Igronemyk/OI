#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 5e5;
const int BUFFER_SIZE = 3;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct UFS {
    int *fathers;

    UFS(int size) {
        fathers = new int[size];
        for(int i = 0;i < size;i++) fathers[i] = i;
    }

    int getFather(int pos) {
        if(fathers[pos] == pos) return pos;
        fathers[pos] = getFather(fathers[pos]);
        return fathers[pos];
    }

    void merge(int u,int v) {
        u = getFather(u);
        v = getFather(v);
        if(u == v) return;
        fathers[u] = v;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }
};

struct TreapNode {
    int ch[2],value,sign,priority,size;

    TreapNode() : value(0) , sign(-2) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value,int sign) : value(value) , sign(sign) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0,gcStk[MAX_TREAP_NODE_SIZE],gcSize = 0;

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value,int sign) {
        int nodeSign;
        if(gcSize != 0) {
            nodeSign = gcStk[gcSize];
            gcSize--;
        }else {
            nodeSign = ++treapSize;
        }
        tn[nodeSign] = TreapNode(value,sign);
        return nodeSign;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(tn[now].ch[0],k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(tn[a].ch[1],b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,tn[b].ch[0]);
            updateInfo(b);
            return b;
        }
    }

    int lowerCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            if(tn[now].value < value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    void insert(int value,int sign) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value,sign);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void join(Treap &otherTreap) {
        travel(otherTreap.root);
        otherTreap.root = 0;
    }

    void travel(int now) {
        if(now == 0) return;
        travel(tn[now].ch[0]);
        insert(tn[now].value,tn[now].sign);
        travel(tn[now].ch[1]);
        gcStk[++gcSize] = now;
    }

    int getKthSign(int k) {
        DRoot tmp1 = split(root,k - 1),tmp2 = split(tmp1.second,1);
        int result = tn[tmp2.first].sign;
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

    int size() {
        return tn[root].size;
    }

    static Treap merge(Treap &t1,Treap &t2) {
        if(t1.size() > t2.size()) {
            t1.join(t2);
            return t1;
        }else {
            t2.join(t1);
            return t2;
        }
    }

};

int main() {
    int n = read<int>(),m = read<int>();
    Treap *treaps = new Treap[n];
    UFS ufs(n);
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        treaps[i].insert(tmpValue,i);
    }
    while(m--) {
        int u = read<int>(),v = read<int>();
        if(u == 0 || v == 0) continue;
        u--; v--;
        if(!ufs.isLinked(u,v)) {
            int signU = ufs.getFather(u),signV = ufs.getFather(v);
            ufs.merge(u,v);
            int newSign = ufs.getFather(u);
            treaps[newSign] = Treap::merge(treaps[signU],treaps[signV]);
        }
    }
    int q = read<int>();
    char *buffer = new char[BUFFER_SIZE + 1];
    while(q--) {
        scanf("%s",buffer);
        if(buffer[0] == 'Q') {
            int sign = read<int>(),k = read<int>();
            sign--;
            sign = ufs.getFather(sign);
            printf("%d\n",treaps[sign].getKthSign(k) + 1);
        }else {
            int u = read<int>(),v = read<int>();
            u--; v--;
            if(!ufs.isLinked(u,v)) {
                int signU = ufs.getFather(u),signV = ufs.getFather(v);
                ufs.merge(u,v);
                int newSign = ufs.getFather(u);
                treaps[newSign] = Treap::merge(treaps[signU],treaps[signV]);
            }
        }
    }
    return 0;
}
