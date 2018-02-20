#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
#include <cstddef>
#include <climits>

using namespace std;

const int MAXN = 500010;
const int MAX_TREAP_NODE_SIZE = 10000010;
const int INF = INT_MAX;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 +c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,version,priority,size;
    TreapNode() : value(0) , version(-1) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value,int version) : value(value) , version(version) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }

} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {
    int root,version;

    typedef pair<int,int> DRoot;

    Treap() : root(-1) , version(-1) { }

    Treap(int version) : root(0) , version(version) { }

    Treap(int root,int version) : root(root) , version(version) { }

    int newNode(int value) {
        tn[++treapSize] = TreapNode(value,version);
        return treapSize;
    }

    int copyNode(int sign) {
        if(sign == 0) return 0;
        if(tn[sign].version == version) return sign;
        tn[++treapSize] = tn[sign];
        tn[treapSize].version = version;
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(copyNode(tn[a].ch[1]),b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,copyNode(tn[b].ch[0]));
            updateInfo(b);
            return b;
        }
    }

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(copyNode(tn[now].ch[0]),k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(copyNode(tn[now].ch[1]),k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
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

    int upperCount(int value) {
        int result = 0,now = root;
        while(now != 0) {
            if(tn[now].value <= value) {
                result += tn[tn[now].ch[0]].size + 1;
                now = tn[now].ch[1];
            }else {
                now = tn[now].ch[0];
            }
        }
        return result;
    }

    bool checkValue(int value) {
        int now = root;
        while(now != 0) {
            if(tn[now].value < value) {
                now = tn[now].ch[1];
            }else if(tn[now].value > value) {
                now = tn[now].ch[0];
            }else {
                return true;
            }
        }
        return false;
    }

    int getKth(int rank) {
        int now = root;
        while(now != 0) {
            int leftChildSize = tn[tn[now].ch[0]].size;
            if(leftChildSize == rank) {
                return now;
            }else if(leftChildSize > rank) {
                now = tn[now].ch[0];
            }else {
                rank -= leftChildSize + 1;
                now = tn[now].ch[1];
            }
        }
        return -1;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void remove(int value) {
        if(!checkValue(value)) return;
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    int getPre(int value) {
        int cnt = lowerCount(value);
        if(cnt == 0) return -INF;
        return tn[getKth(cnt - 1)].value;
    }

    int getSuc(int value) {
        int cnt = upperCount(value);
        if(cnt == tn[root].size) return INF;
        return tn[getKth(cnt)].value;
    }

    Treap copy(int newVersion) {
        Treap result(root,newVersion);
        result.root = result.copyNode(root);
        return result;
    }

};

int main() {
    int N = read<int>();
    Treap *versions = new Treap[N + 1];
    versions[0] = Treap(0);
    for(int i = 1;i <= N;i++) {
        int oldVersion = read<int>(),opt = read<int>(),x = read<int>();
        versions[i] = versions[oldVersion].copy(i);
        Treap &tmpTreap = versions[i];
        switch(opt) {
            case 1: {
                tmpTreap.insert(x);
                break;
            }
            case 2: {
                tmpTreap.remove(x);
                break;
            }
            case 3: {
                printf("%d\n",tmpTreap.lowerCount(x) + 1);
                break;
            }
            case 4: {
                printf("%d\n",tn[tmpTreap.getKth(x - 1)].value);
                break;
            }
            case 5: {
                printf("%d\n",tmpTreap.getPre(x));
                break;
            }
            case 6: {
                printf("%d\n",tmpTreap.getSuc(x));
                break;
            }
        }
    }
    return 0;
}
