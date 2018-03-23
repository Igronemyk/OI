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

struct LCT {
    struct Node {
        Node *father,*childs[2];
        int size,virtualSize,reverseTag;

        Node() : father(NULL) , size(1) , virtualSize(0) , reverseTag(0) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

    } **nodes;

    LCT() : nodes(NULL) { }
    LCT(int size) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) {
            nodes[i] = new Node();
        }
    }

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->childs[0] != now && now->father->childs[1] != now;
    }

    void updateInfo(Node *now) {
        now->size = size(now->childs[0]) + size(now->childs[1]) + now->virtualSize + 1;
    }

    int size(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        int direction = now == father->childs[0];
        if(!isRoot(father)) {
            anc->childs[anc->childs[1] == father] = now;
        }
        now->father = anc;
        father->father = now;
        father->childs[!direction] = now->childs[direction];
        if(father->childs[!direction] != NULL) {
            father->childs[!direction]->father = father;
        }
        now->childs[direction] = father;
        updateInfo(father);
        updateInfo(now);
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(now->reverseTag == 0) return;
        updateReverseTag(now->childs[0]);
        updateReverseTag(now->childs[1]);
        swap(now->childs[0],now->childs[1]);
        updateReverseTag(now);
    }

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->reverseTag ^= 1;
    }

    void notifyAll(Node *now) {
        if(!isRoot(now)) notifyAll(now->father);
        pushDown(now);
    }

    void splay(Node *now) {
        if(now == NULL) return;
        notifyAll(now);
        while(!isRoot(now)) {
            Node *father = now->father,*anc = father->father;
            if(!isRoot(father)) {
                if((father->childs[0] == now) ^ (anc->childs[0] == father)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void access(Node *now) {
        Node *prev = NULL;
        for(Node *doing = now;doing != NULL;doing = doing->father) {
            splay(doing);
            doing->virtualSize += size(doing->childs[1]);
            doing->childs[1] = prev;
            doing->virtualSize -= size(prev);
            updateInfo(doing);
            prev = doing;
        }
    }

    void makeRoot(Node *now) {
        access(now);
        splay(now);
        updateReverseTag(now);
    }

    void link(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        makeRoot(nodeU);
        makeRoot(nodeV);
        nodeU->father = nodeV;
        nodeV->virtualSize += nodeU->size;
        updateInfo(nodeV);
    }
};

int main() {
    return 0;
}
