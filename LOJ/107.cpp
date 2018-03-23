#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstddef>
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
        int value,priority,size;
        Node *childs[2];

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

    Treap() : root(NULL) {
        srand(12345);
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    Node *findKth(int rank) {
        Node *now = root;
        while(now != NULL) {
            int leftChildSize = getSize(now->childs[0]);
            if(leftChildSize == rank) {
                break;
            }else if(leftChildSize > rank) {
                now = now->childs[0];
            }else {
                rank -= leftChildSize + 1;
                now = now->childs[1];
            }
        }
        return now;
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

    int upperCount(int value) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(now->value <= value) {
                result += getSize(now->childs[0]) + 1;
                now = now->childs[1];
            }else {
                now = now->childs[0];
            }
        }
        return result;
    }

    void insert(int value) {
        int k = lowerCount(value);
        DRoot roots = split(root,k);
        Node *newNode = new Node(value);
        root = merge(roots.first,merge(newNode,roots.second));
    }

    void remove(int value) {
        int k = lowerCount(value);
        DRoot roots = split(root,k);
        root = merge(roots.first,split(roots.second,1).second);
    }

    Node *getPrecursor(int value) {
        int cnt = lowerCount(value);
        if(cnt == 0) return NULL;
        return findKth(cnt - 1);
    }

    Node *getSuccessor(int value) {
        int cnt = upperCount(value);
        if(cnt == root->size) return NULL;
        return findKth(cnt);
    }

    int getRankByValue(int value) {
        return lowerCount(value) + 1;
    }

    int getValueByRank(int rank) {
        return findKth(rank - 1)->value;
    }

    int getPrecursorVal(int value) {
        Node *now = getPrecursor(value);
        if(now == NULL) return -1;
        return now->value;
    }

    int getSuccessorVal(int value) {
        Node *now = getSuccessor(value);
        if(now == NULL) return -1;
        return now->value;
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
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - 1);
            now->childs[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }
};

int main() {
    int n = read<int>();
    Treap treap;
    while(n--) {
        int opt = read<int>(),x = read<int>();
        opt++;
        switch(opt) {
            case 1: {
                treap.insert(x);
                break;
            }
            case 2: {
                treap.remove(x);
                break;
            }
            case 4: {
                printf("%d\n",treap.getRankByValue(x) - 1);
                break;
            }
            case 3: {
                printf("%d\n",treap.getValueByRank(x));
                break;
            }
            case 5: {
                printf("%d\n",treap.getPrecursorVal(x));
                break;
            }
            case 6: {
                printf("%d\n",treap.getSuccessorVal(x));
                break;
            }
        }
    }
    return 0;
}
