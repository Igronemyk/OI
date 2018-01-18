#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstddef>
#include <utility>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct Stack {
    T *values;
    int tail;

    Stack(int size) {
        values = new T[size];
        tail = 0;
    }

    void push(T value) {
        values[tail++] = value;
    }

    T top() {
        return values[tail - 1];
    }

    void pop() {
        tail--;
    }

    int size() {
        return tail;
    }

    bool empty() {
        return tail == 0;
    }

    void clear() {
        tail = 0;
    }
};

struct Treap {

    struct Node {
        Node *childs[2];
        int value,priority,size;
        bool rev;

        Node() : value(-1) , priority(-1) , size(-1) , rev(false) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value,int priority) : value(value) , priority(priority) , size(1) , rev(false) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value) : value(value) , priority(rand() % INF) , size(1) , rev(false) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    Node *root;

    Treap() : root(NULL) {
        srand(123456);
    }

    typedef pair<Node *,Node *> DRoot;

    static void updateInfo(Node *now) {
        if(now == NULL) return;
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(!now->rev) return;
        updateReverseTag(now->childs[0]);
        updateReverseTag(now->childs[1]);
        swap(now->childs[0],now->childs[1]);
        updateReverseTag(now);
    }

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
    }

    Node *merge(Node *a,Node *b) {
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

    void reverse(int left,int right) {
        DRoot tmp1 = split(root,left - 1),tmp2 = split(tmp1.second,right - left + 1);
        updateReverseTag(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    DRoot split(Node *now,int k) {
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

    void print() {
        print(root);
        printf("\n");
    }

    void print(Node *now) {
        if(now == NULL) return;
        pushDown(now);
        print(now->childs[0]);
        printf("%d ",now->value);
        print(now->childs[1]);
    }

    static Node *buildTree(int *values,int size,Stack<Node *> *stk) {
        Node *tmpRoot = new Node(-INF,INF);
        stk->push(tmpRoot);
        for(int i = 0;i < size;i++) {
            Node *tmpNode = new Node(values[i]),*prev = NULL;
            while(stk->top()->priority < tmpNode->priority) {
                prev = stk->top();
                updateInfo(prev);
                stk->pop();
            }
            if(prev != NULL) {
                tmpNode->childs[0] = prev;
            }
            stk->top()->childs[1] = tmpNode;
            stk->push(tmpNode);
        }
        while(!stk->empty()) {
            Node *tmp = stk->top();
            updateInfo(tmp);
            stk->pop();
        }
        return tmpRoot->childs[1];
    }

};

int main() {
    int n = read<int>(),m = read<int>();
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = i + 1;
    }
    Stack<Treap::Node *> *stk = new Stack<Treap::Node *>(n);
    Treap treap;
    treap.root = Treap::buildTree(values,n,stk);
    while(m--) {
        int left = read<int>(),right = read<int>();
        treap.reverse(left,right);
    }
    treap.print();
    return 0;
}
