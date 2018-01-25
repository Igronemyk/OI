#include <cstdio>
#include <algorithm>
#include <cstring>
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
        Node *ch[2];
        int value,leftMaxValue,rightMaxValue,maxValue,sumValue,size;

        Node(int value) : value(value) , leftMaxValue(max(0,value)) , rightMaxValue(max(0,value)) , maxValue(value) , sumValue(value) , size(1) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getLeftMaxValue(Node *now) {
        if(now == NULL) return 0;
        return now->leftMaxValue;
    }

    static int getRightMaxValue(Node *now) {
        if(now == NULL) return 0;
        return now->rightMaxValue;
    }

    static int getMaxValue(Node *now) {
        if(now == NULL) return -INF;
        return now->maxValue;
    }

    static int getSumValue(Node *now) {
        if(now == NULL) return 0;
        return now->sumValue;
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        if(now == NULL) return;
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
        now->leftMaxValue = max(getLeftMaxValue(now->ch[0]),getSumValue(now->ch[0]) + now->value + getLeftMaxValue(now->ch[1]));
        now->rightMaxValue = max(getRightMaxValue(now->ch[1]),getSumValue(now->ch[1]) + now->value + getRightMaxValue(now->ch[0]));
        now->maxValue = max(max(getMaxValue(now->ch[0]),getMaxValue(now->ch[1])),getRightMaxValue(now->ch[0]) + now->value + getLeftMaxValue(now->ch[1]));
        now->sumValue = getSumValue(now->ch[0]) + getSumValue(now->ch[1]) + now->value;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        bool flag = rand() & 1;
        if(flag) {
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

    void insert(int value) {
        Node *newNode = new Node(value);
        root = merge(root,newNode);
    }

    void changeValue(int pos,int value) {
        DRoot tmp1 = split(root,pos - 1),tmp2 = split(tmp1.second,1);
        tmp2.first = new Node(value);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    int getMaxValueOfRange(int left,int right) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        int result = getMaxValue(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return result;
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->ch[0]);
        printf("%d ",now->value);
        print(now->ch[1]);
    }


};

int main() {
    int N = read<int>();
    Treap treap;
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>();
        treap.insert(tmpValue);
    }
    int M = read<int>();
    while(M--) {
        int opt = read<int>(),x = read<int>(),y = read<int>();
        if(opt == 0) {
            treap.changeValue(x,y);
        }else {
            printf("%d\n",treap.getMaxValueOfRange(x,y));
        }
    }
    return 0;
}
