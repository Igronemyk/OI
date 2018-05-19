#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 4e5;
const int MAX_ABLE_CNT = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TreapNode {
    int ch[2],priority,value,size;
    bool rev;

    TreapNode() : priority(0) , value(0) , size(0) , rev(false) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(int value) : priority(rand()) , value(value) , size(1) , rev(false) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0;

struct Treap {
    typedef pair<int,int> DRoot;

    int root;

    Treap() : root(0) { }

    Treap(int *values,int size) : root(buildTree(0,size - 1,values)) { }

    int newNode(int value) {
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    void updateRevTag(int now) {
        if(now == 0) return;
        tn[now].rev = !tn[now].rev;
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(!tn[now].rev) return;
        updateRevTag(tn[now].ch[0]);
        updateRevTag(tn[now].ch[1]);
        swap(tn[now].ch[0],tn[now].ch[1]);
        updateRevTag(now);
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        pushDown(a);
        pushDown(b);
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
        pushDown(now);
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

    void reverse(int left,int right) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        updateRevTag(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    int getMinValue() {
        DRoot tmp = split(root,1);
        int result = tn[tmp.first].value;
        root = merge(tmp.first,tmp.second);
        return result;
    }

    int buildTree(int left,int right,int *values) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        int now = newNode(values[mid]);
        tn[now].ch[0] = buildTree(left,mid - 1,values);
        tn[now].ch[1] = buildTree(mid + 1,right,values);
        updateInfo(now);
        return now;
    }
};

int main() {
    int N = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    Treap treap(values,N);
    int cnt = 0;
    bool solved = false;
    while(cnt <= MAX_ABLE_CNT) {
        int value = treap.getMinValue();
        if(value == 1) {
            solved = true;
            break;
        }
        treap.reverse(1,value);
        cnt++;
    }
    if(!solved) {
        printf("-1\n");
    }else {
        printf("%d\n",cnt);
    }
    return 0;
}
