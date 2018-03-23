#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
struct LeftTree {
    struct Node {
        Node *ch[2];
        int dis;
        T value;

        Node(T value) : dis(0) , value(value) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;

    LeftTree() : root(NULL) { }

    LeftTree(T value) : root(new Node(value)) { }

    static void updateDis(Node *now) {
        now->dis = now->ch[1] != NULL ? now->ch[1]->dis + 1 : 0;
    }

    void merge(LeftTree<T> *otherTree) {
        root = merge(root,otherTree->root);
    }

    T getRootValue() {
        if(root == NULL) return T();
        return root->value;
    }

    void deleteMin() {
        if(root == NULL) return;
        root = merge(root->ch[0],root->ch[1]);
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(b->value < a->value) {
            swap(a,b);
        }
        a->ch[1] = merge(a->ch[1],b);
        if(a->ch[0] == NULL || a->ch[0]->dis < a->ch[1]->dis) {
            swap(a->ch[0],a->ch[1]);
        }
        updateDis(a);
        return a;
    }
};

struct BCS {
    int *father,size;
    BCS(int size) : size(size) {
        father = new int[size + 1];
        for(int i = 0;i <= size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faV] = faU;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

};

struct Info {
    int value,index;
    Info() : value(-1) , index(-1) { }
    Info(int value,int index) : value(value) , index(index) { }

    bool operator < (const Info &otherInfo) const {
        if(value != otherInfo.value) {
            return value < otherInfo.value;
        }else {
            return index < otherInfo.index;
        }
    }

};

int main() {
    int N = read<int>(),M = read<int>();
    BCS bcset(N);
    LeftTree<Info> **trees = new LeftTree<Info>*[N];
    bool *isDeleted = new bool[N];
    memset(isDeleted,false,sizeof(bool) * N);
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>();
        trees[i] = new LeftTree<Info>(Info(tmpValue,i));
    }
    while(M--) {
        int opt = read<int>();
        switch(opt) {
            case 1: {
                int x = read<int>(),y = read<int>();
                x--; y--;
                if(isDeleted[x] || isDeleted[y] || bcset.isLinked(x,y)) {
                    break;
                }
                int posX = bcset.getFather(x),posY = bcset.getFather(y);
                trees[posX]->merge(trees[posY]);
                bcset.merge(posX,posY);
                break;
            }
            case 2: {
                int x = read<int>();
                x--;
                if(isDeleted[x]) {
                    printf("-1\n");
                    break;
                }
                int posX = bcset.getFather(x);
                printf("%d\n",trees[posX]->getRootValue().value);
                isDeleted[trees[posX]->getRootValue().index] = true;
                trees[posX]->deleteMin();
                break;
            }
        }
    }
    return 0;
}
