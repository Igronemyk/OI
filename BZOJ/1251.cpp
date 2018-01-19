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
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Treap {
    struct Node {
        Node *childs[2];
        int value,priority,size,maxValue,addTag;
        bool rev;

        Node(int value) : value(value) , priority(rand()) , size(1) , maxValue(value) , addTag(0) , rev(false) {
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

    static int getMaxValue(Node *now) {
        if(now == NULL) return -INF;
        return now->maxValue;
    }

    static void pushDown(Node *now) {
        if(now == NULL) return;
        if(now->addTag) {
            updateAddTag(now->childs[0],now->addTag);
            updateAddTag(now->childs[1],now->addTag);
            now->addTag = 0;
        }
        if(now->rev) {
            now->rev = false;
            updateReverseTag(now->childs[0]);
            updateReverseTag(now->childs[1]);
        }
    }

    static void updateAddTag(Node *now,int tag) {
        if(now == NULL) return;
        now->addTag += tag;
        now->value += tag;
        now->maxValue += tag;
    }

    static void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
        swap(now->childs[0],now->childs[1]);
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
        now->maxValue = max(getMaxValue(now->childs[0]),max(now->value,getMaxValue(now->childs[1])));
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

    void addValue(int left,int right,int value) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        updateAddTag(tmp2.first,value);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    void reverse(int left,int right) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        updateReverseTag(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    int getMaxValue(int left,int right) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        int result = tmp2.first->maxValue;
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

    void print() {
        print(root);
    }

    void print(Node *now) {
        if(now == NULL) return;
        pushDown(now);
        print(now->childs[0]);
        printf("%d ",now->value);
        print(now->childs[1]);
    }

};

int main() {
    int N = read<int>(),M = read<int>();
    Treap treap;
    for(int i = 0;i < N;i++) {
        treap.insert(0);
    }
    while(M--) {
        int opt = read<int>(),left = read<int>(),right = read<int>();
        switch(opt) {
            case 1: {
                int value = read<int>();
                treap.addValue(left,right,value);
                break;
            }
            case 2: {
                treap.reverse(left,right);
                break;
            }
            case 3: {
                printf("%d\n",treap.getMaxValue(left,right));
                break;
            }
        }
    }
    return 0;
}
