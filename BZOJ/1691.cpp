#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <climits>
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

struct Treap {
    struct Node {
        Node *childs[2];
        int value,priority,size;

        Node() : value(-1) , priority(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value) : value(value) , priority(rand()) , size(1) {
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

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
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

    int lowerCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value < value) {
                result += getSize(now->childs[0]) + 1;
                now = now->childs[1];
            }else {
                now = now->childs[0];
            }
        }
        return result;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        Node *newNode = new Node(value);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    int lowerBound(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        if(tmp.second == NULL) return -1;
        DRoot tmp2 = split(tmp.second,1);
        int result = tmp2.first->value;
        root = merge(tmp.first,merge(tmp2.first,tmp2.second));
        return result;
    }
};

struct Info {
    int weight,fresh;

    Info() : weight(-1) , fresh(-1) { }

    Info(int weight,int fresh) : weight(weight) , fresh(fresh) { }

    bool operator < (const Info &otherInfo) const {
        return this->fresh > otherInfo.fresh;
    }

};

int main() {
    srand(123456);
    int N = read<int>(),M = read<int>();
    Info *cows = new Info[N],*grass = new Info[M];
    for(int i = 0;i < N;i++) {
        cows[i].weight = read<int>();
        cows[i].fresh = read<int>();
    }
    sort(cows,cows + N);
    for(int i = 0;i < M;i++) {
        grass[i].weight = read<int>();
        grass[i].fresh = read<int>();
    }
    sort(grass,grass + M);
    int nowPos = 0;
    Treap treap;
    long long result = 0;
    for(int i = 0;i < N;i++) {
        for(;nowPos < M;nowPos++) {
            if(grass[nowPos].fresh >= cows[i].fresh) {
                treap.insert(grass[nowPos].weight);
            }else {
                break;
            }
        }
        int value = treap.lowerBound(cows[i].weight);
        if(value == -1) {
            printf("-1\n");
            return 0;
        }
        result += value;
        treap.remove(value);
    }
    printf("%lld\n",result);
    return 0;
}
