#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MODDER = 1000000;

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

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        Node *newNode = new Node(value);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        DRoot tmp2 = split(tmp.second,1);
        root = merge(tmp.first,tmp2.second);
    }

    Node *getPrecursor(int value) {
        return findKth(lowerCount(value) - 1);
    }

    Node *getSuccessor(int value) {
        return findKth(upperCount(value));
    }

    int getResult(int value) {
        int diff = INF;
        bool isPrecursor = true;
        Node *precursor = getPrecursor(value);
        if(precursor != NULL) {
            int tmpValue = precursor->value;
            diff = min(diff,abs(value - tmpValue));
        }
        Node *successor = getSuccessor(value);
        if(successor != NULL) {
            int tmpValue = successor->value;
            if(diff > abs(value - tmpValue)) {
                diff = abs(value - tmpValue);
                isPrecursor = false;
            }
        }
        if(isPrecursor) {
            remove(precursor->value);
        }else {
            remove(successor->value);
        }
        return diff;
    }

    void print() {
        print(root);
        printf("\n");
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->childs[0]);
        printf("[%d,%d] ",now->value,now->size);
        print(now->childs[1]);
    }

};

int main() {
    srand(123456);
    int countPet = 0,countPerson = 0;
    int n = read<int>(),result = 0;
    Treap treap;
    while(n--) {
        int a = read<int>(),b = read<int>();
        if(a == 0) {
            if(countPerson > 0) {
                countPerson--;
                result = (result + treap.getResult(b)) % MODDER;
            }else {
                countPet++;
                treap.insert(b);
            }
        }else {
            if(countPet > 0) {
                countPet--;
                result = (result + treap.getResult(b)) % MODDER;
            }else {
                countPerson++;
                treap.insert(b);
            }
        }
    }
    printf("%d\n",result);
    return 0;
}
