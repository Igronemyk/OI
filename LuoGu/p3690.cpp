#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0; int f = 1; char c = getchar();
    while (c > '9' || c < '0') { if (c == '-') f *= -1; c = getchar(); }
    while (c <= '9' && c >= '0') { result = result * 10 + c - '0'; c = getchar(); }
    return result * f;
}

struct LCT {
    struct Node {
        Node *father, *childs[2];
        int sign,value, xorValue, reverseTag;
        Node() : father(NULL), sign(-1) , value(-1), xorValue(-1), reverseTag(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(Node *father, int value,int sign) : father(father), sign(sign) , value(value), xorValue(value), reverseTag(0) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    } **nodes;

    int size, nowSize;

    LCT() : size(size), nowSize(-1), nodes(NULL) { }

    LCT(int size) : size(size), nowSize(0) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) nodes[i] = NULL;
    }

    bool isRoot(Node *now) {
        if (now->father == NULL) return true;
        return now->father->childs[0] != now && now->father->childs[1] != now;
    }

    void rotate(Node *now) {
        Node *father = now->father, *anc = father->father;
        if (!isRoot(father)) {
            anc->childs[anc->childs[1] == father] = now;
        }
        int direction = father->childs[0] == now;
        now->father = anc;
        father->father = now;
        father->childs[!direction] = now->childs[direction];
        if (father->childs[!direction] != NULL) {
            father->childs[!direction]->father = father;
        }
        now->childs[direction] = father;
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now) {
        if (now == NULL) return;
        notifyAll(now);
        while (!isRoot(now)) {
            Node *father = now->father, *anc = father->father;
            if (!isRoot(father)) {
                if ((father->childs[0] == now) ^ (anc->childs[0] == father)) {
                    rotate(now);
                }
                else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void insert(int value) {
        nodes[nowSize] = new Node(NULL, value,nowSize + 1);
        nowSize++;
    }

    void access(int pos) {
        Node *prev = NULL;
        for (Node *now = nodes[pos]; now != NULL; now = now->father) {
            splay(now);
            now->childs[1] = prev;
            updateInfo(now);
            prev = now;
        }
    }

    void makeRoot(int pos) {
        access(pos);
        splay(nodes[pos]);
        updateReverseTag(nodes[pos]);
    }

    Node* findFather(int pos) {
        access(pos);
        splay(nodes[pos]);
        Node *now = nodes[pos];
        while (now->childs[0] != NULL) {
            now = now->childs[0];
        }
        return now;
    }

    void split(int u, int v) {
        makeRoot(u);
        access(v);
        splay(nodes[v]);
    }

    bool isLinked(int u, int v) {
        Node *faU = findFather(u), *faV = findFather(v);
        return faU == faV;
    }

    void cut(int u, int v) {
        if (isLinked(u, v)) {
            split(u, v);
            if (nodes[v]->childs[0] == nodes[u]) {
                nodes[v]->childs[0] = NULL;
                updateInfo(nodes[v]);
                nodes[u]->father = NULL;
            }
        }
    }

    void link(int u, int v) {
        if (!isLinked(u, v)) {
            makeRoot(u);
            nodes[u]->father = nodes[v];
        }
    }

    void changeValue(int pos, int value) {
        access(pos);
        splay(nodes[pos]);
        nodes[pos]->value = value;
        updateInfo(nodes[pos]);
    }


    void notifyAll(Node *now) {
        if(now == NULL) return;
        if (!isRoot(now)) {
            notifyAll(now->father);
        }
        pushDown(now);
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if (now->reverseTag == 0) return;
        updateReverseTag(now->childs[0]);
        updateReverseTag(now->childs[1]);
        updateReverseTag(now);
        swap(now->childs[0], now->childs[1]);
    }

    void updateReverseTag(Node *now) {
        if (now == NULL) return;
        now->reverseTag ^= 1;
    }

    void updateInfo(Node *now) {
        now->xorValue = getXorValue(now->childs[0]) ^ getXorValue(now->childs[1]) ^ now->value;
    }

    int getXorValue(int u, int v) {
        split(u, v);
        return nodes[v]->xorValue;
    }

    int getXorValue(Node *now) {
        if (now == NULL) return 0;
        return now->xorValue;
    }

};

int main() {
    int N = read<int>(), M = read<int>();
    LCT lct(N);
    for (int i = 0; i < N; i++) {
        int value = read<int>();
        lct.insert(value);
    }
    for(int doing = 0;doing < M;doing++) {
        int opt = read<int>(), x = read<int>(), y = read<int>();
        x--; y--;
        switch (opt) {
            case 0: {
                printf("%d\n", lct.getXorValue(x, y));
                break;
            }
            case 1: {
                lct.link(x, y);
                break;
            }
            case 2: {
                lct.cut(x, y);
                break;
            }
            case 3: {
                lct.changeValue(x, y + 1);
                break;
            }
        }
    }
    return 0;
}
