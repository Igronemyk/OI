#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int n,m;

struct Splay {

    struct Node {
        Node *father,*childs[2];
        int lazyTag,value,size;

        Node() : father(NULL) , lazyTag(-1) , value(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
        Node(Node *father,int value) : father(father) , lazyTag(0) , value(value) , size(1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

    };

    Node *root;

    Splay() : root(NULL) { }

    void rotate(Node *now,int direction) {
        Node *father = now->father,*anc = father->father;
        now->father = anc;
        father->father = now;
        if(anc != NULL) {
            anc->childs[anc->childs[1] == father] = now;
        }
        father->childs[!direction] = now->childs[direction];
        if(father->childs[!direction] != NULL) {
            father->childs[!direction]->father = father;
        }
        now->childs[direction] = father;
        if(root == father) {
            root = now;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            if(now->father->father == dist) {
                rotate(now,now->father->childs[0] == now);
            }else {
                Node *father = now->father,*anc = father->father;
                if(anc->childs[0] == father) {
                    if(father->childs[0] == now) {
                        rotate(father,1);
                        rotate(now,1);
                    }else {
                        rotate(now,0);
                        rotate(now,1);
                    }
                }else {
                    if(father->childs[0] == now) {
                        rotate(now,1);
                        rotate(now,0);
                    }else {
                        rotate(father,0);
                        rotate(now,0);
                    }
                }
            }
        }
    }

    void insert(int value) {
        if(root == NULL) {
            root = new Node(NULL,value);
            return;
        }
        Node *now = root,*result = NULL;
        while(true) {
            if(now->value > value) {
                if(now->childs[0] == NULL) {
                    now->childs[0] = new Node(now,value);
                    result = now->childs[0];
                    break;
                }else {
                    now = now->childs[0];
                }
            }else {
                if(now->childs[1] == NULL) {
                    now->childs[1] = new Node(now,value);
                    result = now->childs[1];
                    break;
                }else {
                    now = now->childs[1];
                }
            }
        }
        splay(result,NULL);
    }

    Node *getKth(int rank) {
        if(root == NULL || rank > root->size) return NULL;
        Node *now = root;
        while(true) {
            pushDown(now);
            if(rank == size(now->childs[0]) + 1) {
                break;
            }else if(rank <= size(now->childs[0])) {
                now = now->childs[0];
            }else {
                rank -= size(now->childs[0]) + 1;
                now = now->childs[1];
            }
        }
        return now;
    }

    void pushDown(Node *now) {
        if(now == NULL || now->lazyTag == 0) return;
        updateTag(now->childs[0]);
        updateTag(now->childs[1]);
        swap(now->childs[0],now->childs[1]);
        updateTag(now);
    }

    void reverse(int left,int right) {
        Node *leftPos = getKth(left - 1);
        Node *rightPos = getKth(right + 1);
        splay(leftPos,NULL);
        splay(rightPos,leftPos);
        updateTag(rightPos->childs[0]);
    }

    void updateTag(Node *now) {
        if(now == NULL) return;
        now->lazyTag ^= 1;
    }

    void updateInfo(Node *now) {
        if(now == NULL) return;
        now->size = size(now->childs[0]) + size(now->childs[1]) + 1;
    }

    int size(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void print() {
        print(root);
    }

    void print(Node *now) {
        if(now == NULL) return;
        pushDown(now);
        print(now->childs[0]);
        if(now->value != 0 && now->value != n + 1) printf("%d ",now->value);
        print(now->childs[1]);
    }

};

int main() {
    n = read<int>();
    m = read<int>();
    Splay splay;
    for(int i = 0;i <= n + 1;i++) splay.insert(i);
    while(m--) {
        int left = read<int>(),right = read<int>();
        splay.reverse(left + 1,right + 1);
    }
    splay.print();
    return 0;
}
