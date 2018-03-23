#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCT {
    struct Node {
        Node *father,*ch[2];
        int col,leftCol,rightCol,colCount,lazy;
        bool rev;

        Node(int col) : father(NULL) , col(col) , leftCol(col) , rightCol(col) , colCount(1) , lazy(0) , rev(false) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    } **nodes;

    LCT(int nodeSize,int *colors) {
        nodes = new Node*[nodeSize];
        for(int i = 0;i < nodeSize;i++) {
            nodes[i] = new Node(colors[i]);
        }
    }

    bool isRoot(Node *now) {
        if(now == NULL) return true;
        if(now->father == NULL) return true;
        return now->father->ch[0] != now && now->father->ch[1] != now;
    }

    void updateInfo(Node *now) {
        if(now == NULL) return;
        now->colCount = 1;
        now->leftCol = now->col;
        now->rightCol = now->col;
        if(now->ch[0] != NULL) {
            now->leftCol = now->ch[0]->leftCol;
            now->colCount += now->ch[0]->colCount;
            if(now->col == now->ch[0]->rightCol) {
                now->colCount--;
            }
        }
        if(now->ch[1] != NULL) {
            now->rightCol = now->ch[1]->rightCol;
            now->colCount += now->ch[1]->colCount;
            if(now->col == now->ch[1]->leftCol) {
                now->colCount--;
            }
        }
    }

    void updateRevTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
        swap(now->ch[0],now->ch[1]);
        swap(now->leftCol,now->rightCol);
    }

    void updateLazyTag(Node *now,int tag) {
        if(now == NULL) return;
        now->lazy = tag;
        now->col = tag;
        now->leftCol = now->col;
        now->rightCol = now->col;
        now->colCount = 1;
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(now->lazy != 0) {
            updateLazyTag(now->ch[0],now->lazy);
            updateLazyTag(now->ch[1],now->lazy);
            now->lazy = 0;
        }
        if(now->rev) {
            updateRevTag(now->ch[0]);
            updateRevTag(now->ch[1]);
            now->rev = false;
        }
    }

    void notifyAll(Node *now) {
        if(now == NULL) return;
        if(!isRoot(now)) notifyAll(now->father);
        pushDown(now);
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(!isRoot(father)) {
            anc->ch[anc->ch[1] == father] = now;
        }
        now->father = anc;
        father->father = now;
        int direction = father->ch[0] == now;
        father->ch[!direction] = now->ch[direction];
        now->ch[direction] = father;
        if(father->ch[!direction] != NULL) {
            father->ch[!direction]->father = father;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now) {
        if(now == NULL) return;
        notifyAll(now);
        while(!isRoot(now)) {
            Node *father = now->father,*anc = father->father;
            if(!isRoot(father)) {
                if((father->ch[0] == now) ^ (anc->ch[0] == father)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void access(int pos) {
        Node *prev = NULL;
        for(Node *now = nodes[pos];now != NULL;now = now->father) {
            splay(now);
            now->ch[1] = prev;
            updateInfo(now);
            prev = now;
        }
    }

    void makeRoot(int pos) {
        Node *now = nodes[pos];
        access(pos);
        splay(now);
        updateRevTag(now);
    }

    void split(int u,int v) {
        makeRoot(u);
        access(v);
        splay(nodes[v]);
    }

    void link(int u,int v) {
        makeRoot(u);
        nodes[u]->father = nodes[v];
    }

    void makeSame(int u,int v,int col) {
        split(u,v);
        updateLazyTag(nodes[v],col);
    }

    int getValue(int u,int v) {
        split(u,v);
        return nodes[v]->colCount;
    }

};

int main() {
    int n = read<int>(),m = read<int>(),*values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
    }
    LCT lct(n,values);
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        lct.link(u,v);
    }
    char *buffer = new char[BUFFER_SIZE + 1];
    while(m--) {
        scanf("%s",buffer);
        if(buffer[0] == 'C') {
            int u = read<int>(),v = read<int>(),col = read<int>();
            u--; v--;
            lct.makeSame(u,v,col);
        }else {
            int u = read<int>(),v = read<int>();
            u--; v--;
            printf("%d\n",lct.getValue(u,v));
        }
    }
    return 0;
}
