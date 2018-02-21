#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data {
    int s,c,m;

    bool operator < (const Data &otherData) const {
        if(s != otherData.s) {
            return s < otherData.s;
        }
        if(c != otherData.c) {
            return c < otherData.c;
        }
        if(m != otherData.m) {
            return m < otherData.m;
        }
        return false;
    }

    bool operator == (const Data &otherData) const {
        return s == otherData.s && c == otherData.c && m == otherData.m;
    }
};

struct Treap {
    struct Node {
        Node *ch[2];
        int value,priority,size;

        Node(int value) : value(value) , priority(rand()) , size(1) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        if(now == NULL) return;
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
    }

    static Node *merge(Node *a,Node*b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority > b->priority) {
            a->ch[1] = merge(a->ch[1],b);
            updateInfo(a);
            return a;
        }else {
            b->ch[0] = merge(a,b->ch[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->ch[0])) {
            result = split(now->ch[0],k);
            now->ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->ch[1],k - getSize(now->ch[0]) - 1);
            now->ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value < value) {
                result += getSize(now->ch[0]) + 1;
                now = now->ch[1];
            }else {
                now = now->ch[0];
            }
        }
        return result;
    }

    int upperCount(int value) {
        return lowerCount(value + 1);
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        Node *newNode = new Node(value);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }
};

struct BIT {
    Treap *values;
    int size;

    BIT(int size) : size(size) {
        values = new Treap[size + 1];
    }

    void update(int pos,int val) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i].insert(val);
        }
    }

    int getNotGreaterThan(int pos,int val) {
        int result = 0;
        while(pos) {
            result += values[pos].upperCount(val);
            pos -= lowbit(pos);
        }
        return result;
    }

    int lowbit(int value) {
        return value & -value;
    }

};

int main() {
    int N = read<int>(),K = read<int>(),*results = new int[N];
    memset(results,0,sizeof(int) * N);
    BIT bitree(K);
    Data *datas = new Data[N];
    for(int i = 0;i < N;i++) {
        datas[i].s = read<int>();
        datas[i].c = read<int>();
        datas[i].m = read<int>();
    }
    sort(datas,datas + N);
    int nowCount = 0;
    for(int i = 0;i < N;i++) {
        Data &tmpData = datas[i];
        if(i < N - 1 && datas[i] == datas[i + 1]) {
            nowCount++;
        }else {
            int cnt = bitree.getNotGreaterThan(tmpData.c,tmpData.m);
            results[cnt] += nowCount + 1;
            nowCount = 0;
        }
        bitree.update(tmpData.c,tmpData.m);
    }
    for(int i = 0;i < N;i++) {
        printf("%d\n",results[i]);
    }
    return 0;
}

