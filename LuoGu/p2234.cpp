#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>
#include <climits>

using namespace std;

const int INF = INT_MAX;
const int MODDER = 1000000;
const int MAX_TREAP_NODE_SIZE = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],value,priority,size;

    TreapNode() : value(0) , priority(0) , size(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : value(value) , priority(rand()) , size(1) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {

    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    static int newNode(int value) {
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
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
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - 1);
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

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        int newNodeSign = newNode(value);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    int getResult(int value) {
        int cnt = lowerCount(value);
        DRoot tmp1 = split(root,cnt);
        int minDiff = INF;
        if(tn[tmp1.first].size >= 1) {
            DRoot tmp2 = split(tmp1.first,tn[tmp1.first].size - 1);
            minDiff = value - tn[tmp2.second].value;
            tmp1.first = merge(tmp2.first,tmp2.second);
        }
        if(tn[tmp1.second].size >= 1) {
            DRoot tmp2 = split(tmp1.second,1);
            if(minDiff > tn[tmp2.first].value - value) {
                minDiff = tn[tmp2.first].value - value;
            }
            tmp1.second = merge(tmp2.first,tmp2.second);
        }
        root = merge(tmp1.first,tmp1.second);
        return minDiff;
    }
};

int main() {
    srand(123456);
    int n = read<int>();
    int result = 0;
    Treap treap;
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        if(i == 0) {
            result = tmpValue;
            treap.insert(tmpValue);
            continue;
        }
        result += treap.getResult(tmpValue);
        treap.insert(tmpValue);
    }
    printf("%d\n",result);
    return 0;
}
