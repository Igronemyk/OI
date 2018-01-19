#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

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
        long long sum;

        Node() : value(-1) , priority(-1) , size(-1) , sum(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value) : value(value) , priority(rand()) , size(1) , sum(value) {
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

    static long long getSum(Node *now) {
        if(now == NULL) return 0;
        return now->sum;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
        now->sum = getSum(now->childs[0]) + getSum(now->childs[1]) + now->value;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority < b->priority) {
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
            return result;
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - 1);
            now->childs[1] = result.first;
            updateInfo(now);
            result.first = now;
            return result;
        }
    }

    int lowerCount(int value) {
        Node *now = root;
        int result = 0;
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

    pair<long long,int> getResult(int k) {
        DRoot tmp1 = split(root,k / 2),tmp2 = split(tmp1.second,1);
        int midValue = tmp2.first->value;
        long long result =  getSize(tmp1.first) * 1LL * midValue - getSum(tmp1.first);
        result += getSum(tmp2.second) - getSize(tmp2.second) * 1LL * midValue;
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        return make_pair(result,midValue);
    }
};

int main() {
    int n = read<int>(),k = read<int>(),*values = new int[n];
    Treap treap;
    long long ans = INF;
    int pos = -1,midValue = -1;
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        treap.insert(tmpValue);
        values[i] = tmpValue;
        if(i + 1 < k) continue;
        if(i - k >= 0) treap.remove(values[i - k]);
        pair<long long,int> tmpAns = treap.getResult(k);
        if(tmpAns.first < ans) {
            ans = tmpAns.first;
            pos = i;
            midValue = tmpAns.second;
        }
    }
    for(int i = pos;i >= pos - k + 1;i--) {
        values[i] = midValue;
    }
    printf("%lld\n",ans);
    for(int i = 0;i < n;i++) {
        printf("%d\n",values[i]);
    }
    return 0;
}
