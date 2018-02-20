#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

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
        int priority,cnt,size;
        long long value;

        Node(long long value,int cnt) : value(value) , priority(rand()) , cnt(cnt) , size(cnt) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() {
        root = NULL;
    }

    Treap(long long startSign,int size) {
        root = new Node(startSign,size);
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + now->cnt;
    }

    static Node *merge(Node *a,Node *b) {
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
        }else if(k - getSize(now->ch[0]) < now->cnt) {
            Node *newNode = new Node(now->value,k - getSize(now->ch[0]));
            newNode->ch[0] = now->ch[0];
            now->ch[0] = NULL;
            now->value += newNode->cnt;
            now->cnt -= newNode->cnt;
            updateInfo(newNode);
            updateInfo(now);
            result.first = newNode;
            result.second = now;
        }else {
            result = split(now->ch[1],k - getSize(now->ch[0]) - now->cnt);
            now->ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    void insert(long long value,int cnt) {
        Node *newNode = new Node(value,cnt);
        root = merge(root,newNode);
    }

    long long getSignAndRemove(int pos) {
        DRoot tmp1 = split(root,pos - 1),tmp2 = split(tmp1.second,1);
        long long result = tmp2.first->value;
        root = merge(tmp1.first,tmp2.second);
        return result;
    }
};

int main() {
    int n = read<int>(),m = read<int>(),q = read<int>();
    Treap **rows = new Treap*[n + 1],*rightCol = new Treap();
    for(int i = 1;i <= n;i++) {
        rows[i] = new Treap((i - 1) * 1LL * m + 1,m - 1);
        rightCol->insert((i - 1) * 1LL * m + m,1);
    }
    while(q--) {
        int x = read<int>(),y = read<int>();
        if(y == m) {
            long long tmpSign = rightCol->getSignAndRemove(x);
            printf("%lld\n",tmpSign);
            rightCol->insert(tmpSign,1);
            continue;
        }
        long long tmpSign1 = rows[x]->getSignAndRemove(y);
        long long tmpSign2 = rightCol->getSignAndRemove(x);
        rows[x]->insert(tmpSign2,1);
        rightCol->insert(tmpSign1,1);
        printf("%lld\n",tmpSign1);
    }
    return 0;
}
