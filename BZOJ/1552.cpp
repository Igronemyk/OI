#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data {
    int value,pos;

    bool operator < (const Data &otherData) const {
        if(value != otherData.value) {
            return value < otherData.value;
        }else {
            return pos < otherData.pos;
        }
    }
};

struct Treap {
    struct Node {
        Node *childs[2];
        int value,priority,size,minPos,minValue;
        bool rev;

        Node(int value) : value(value) , priority(rand()) , size(1) , minPos(0) , minValue(value) , rev(false) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static int getMinPos(Node *now) {
        if(now == NULL) return -1;
        return now->minPos;
    }

    static int getMinValue(Node *now) {
        if(now == NULL) return INF;
        return now->minValue;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
        now->minValue = now->value;
        now->minPos = getSize(now->childs[0]);
        if(getMinValue(now->childs[0]) < now->minValue) {
            now->minValue = getMinValue(now->childs[0]);
            now->minPos = getMinPos(now->childs[0]);
        }
        if(getMinValue(now->childs[1]) < now->minValue) {
            now->minValue = getMinValue(now->childs[1]);
            now->minPos = getSize(now->childs[0]) + 1 + getMinPos(now->childs[1]);
        }
    }

    static void pushDown(Node *now) {
        if(now == NULL) return;
        if(!now->rev) return;
        now->rev = false;
        updateReverseTag(now->childs[0]);
        updateReverseTag(now->childs[1]);
    }

    static void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
        swap(now->childs[0],now->childs[1]);
        now->minPos = now->size - now->minPos - 1;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        pushDown(a);
        pushDown(b);
        if(a->priority > b->priority) {
            a->childs[1] = merge(a->childs[1],b);
            updateInfo(a);
            return a;
        }else {
            b->childs[0] = merge(a,b->childs[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        pushDown(now);
        if(k <= getSize(now->childs[0])) {
            result = split(now->childs[0],k);
            now->childs[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - 1);
            now->childs[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    void insert(int value) {
        Node *newNode = new Node(value);
        root = merge(root,newNode);
    }

    int doWork(int pos) {
        DRoot tmp1 = split(root,pos - 1);
        int result = getSize(tmp1.first) + tmp1.second->minPos + 1;
        DRoot tmp2 = split(tmp1.second,tmp1.second->minPos + 1);
        updateReverseTag(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

    void print() {
        print(root);
        printf("\n");
    }

    void print(Node *now) {
        if(now == NULL) return;
        pushDown(now);
        print(now->childs[0]);
        printf("%d " ,now->value);
        print(now->childs[1]);
    }
};

int main() {
    int N = read<int>(),*values = new int[N];
    Data *datas = new Data[N];
    for(int i = 0;i < N;i++) {
        datas[i].value = read<int>();
        datas[i].pos = i;
    }
    sort(datas,datas + N);
    for(int i = 0;i < N;i++) {
        values[datas[i].pos] = i + 2;
    }
    Treap treap;
    for(int i = 0;i < N;i++) {
        int tmpValue = values[i];
        treap.insert(tmpValue);
    }
    for(int i = 0;i < N;i++) {
        printf("%d",treap.doWork(i + 1));
        if(i != N - 1) printf(" ");
    }
    printf("\n");
    return 0;
}

