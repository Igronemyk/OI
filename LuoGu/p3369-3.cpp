#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstddef>
#include <utility>

using namespace std;

struct Treap {
    struct Node {
        int value,priority,cnt,size;
        Node *childs[2];

        Node() : value(-1) , priority(-1) , cnt(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int value) : value(value) , priority(rand()) , cnt(1) , size(1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + now->cnt;
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

    static DRoot *split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->childs[0])) {
            result = split(now->chids[0],k);
            now->childs[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - );
        }
    }
};

int main() {
    return 0;
}
