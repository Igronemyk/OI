#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 3e6;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],priority,value,cnt,size;

    TreapNode() : priority(0) , value(0) , cnt(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value,int cnt) : priority(rand()) , value(value) , cnt(cnt) , size(cnt) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0,gcStk[MAX_TREAP_NODE_SIZE],gcSize = 0;

struct Treap {
    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    Treap(int *values,int size) : root(buildTree(0,size - 1,values)) { }

    int newNode(int value,int cnt) {
        if(gcSize != 0) {
            int sign = gcStk[gcSize--];
            if(tn[sign].ch[0] != 0) {
                gcStk[++gcSize] = tn[sign].ch[0];
            }
            if(tn[sign].ch[1] != 0) {
                gcStk[++gcSize] = tn[sign].ch[1];
            }
            tn[sign] = TreapNode(value,cnt);
            return sign;
        }
        tn[++treapSize] = TreapNode(value,cnt);
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + tn[now].cnt;
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

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(tn[now].ch[0],k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else if(k < tn[tn[now].ch[0]].size + tn[now].cnt) {
            int newNodeSign = newNode(tn[now].value,k - tn[tn[now].ch[0]].size);
            tn[now].value += tn[newNodeSign].cnt;
            tn[now].cnt -= tn[newNodeSign].cnt;
            tn[newNodeSign].ch[0] = tn[now].ch[0];
            tn[now].ch[0] = 0;
            updateInfo(now);
            updateInfo(newNodeSign);
            result.first = newNodeSign;
            result.second = now;
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - tn[now].cnt);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    void insert(int pos,int value,int cnt) {
        DRoot tmp = split(root,pos);
        int newNodeSign = newNode(value,cnt);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void remove(int pos,int cnt) {
        DRoot tmp1 = split(root,pos),tmp2 = split(tmp1.second,cnt);
        gcStk[++gcSize] = tmp2.first;
        root = merge(tmp1.first,tmp2.second);
    }

    int getValue(int pos) {
        DRoot tmp1 = split(root,pos - 1),tmp2 = split(tmp1.second,1);
        int result = tn[tmp2.first].value;
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

    int buildTree(int left,int right,int *values) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        int now = newNode(values[mid],1);
        tn[now].ch[0] = buildTree(left,mid - 1,values);
        tn[now].ch[1] = buildTree(mid + 1,right,values);
        updateInfo(now);
        return now;
    }
};


int main() {
    int n = read<int>(),m = read<int>(),*values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
    }
    Treap treap(values,n);
    while(m--) {
        int opt = read<int>();
        switch(opt) {
            case 0: {
                int p = read<int>(),a = read<int>(),b = read<int>();
                treap.insert(p,a,b - a + 1);
                break;
            }
            case 1: {
                int a = read<int>(),b = read<int>();
                treap.remove(a - 1,b - a + 1);
                break;
            }
            case 2: {
                int p = read<int>();
                printf("%d\n",treap.getValue(p));
                break;
            }
        }
    }
    return 0;
}
