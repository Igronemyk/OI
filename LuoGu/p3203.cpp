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

struct LCT {
    struct Node {
        Node *father,*ch[2];
        int size,sign;
        bool rev;

        Node(int sign) : father(NULL) , size(1) , sign(sign) , rev(false) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    } **nodes;

    LCT(int size) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) {
            nodes[i] = new Node(i);
        }
    }

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->ch[0] != now && now->father->ch[1] != now;
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void updateInfo(Node *now) {
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
    }

    void notifyAll(Node *now) {
        if(now == NULL) return;
        if(!isRoot(now)) notifyAll(now->father);
        pushDown(now);
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(!now->rev) return;
        updateReverseTag(now->ch[0]);
        updateReverseTag(now->ch[1]);
        swap(now->ch[0],now->ch[1]);
        updateReverseTag(now);
    }

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->rev = !now->rev;
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(!isRoot(father)) {
            anc->ch[anc->ch[1] == father] = now;
        }
        father->father = now;
        now->father = anc;
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
                if((anc->ch[0] == father) ^ (father->ch[0] == now)) {
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
        updateReverseTag(now);
    }

    void split(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        makeRoot(u);
        access(v);
        splay(nodeV);
    }

    void link(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        makeRoot(u);
        nodeU->father = nodeV;
    }

    void cut(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        split(u,v);
        if(nodeV->ch[0] == nodeU) {
            nodeV->ch[0] = NULL;
            updateInfo(nodeV);
            nodeU->father = NULL;
        }
    }

    int getSize(int u,int v) {
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        split(u,v);
        return nodeV->size;
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->ch[0]);
        printf("%d ",now->sign);
        print(now->ch[1]);
    }
};

int main() {
    int n = read<int>();
    LCT lct(n + 1);
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>(),distPos = i + tmpValue;
        if(distPos > n) distPos = n;
        lct.link(i,distPos);
        values[i] = distPos;
    }
    int m = read<int>();
    while(m--) {
        int opt = read<int>();
        if(opt == 1) {
            int startPos = read<int>();
            printf("%d\n",lct.getSize(startPos,n) - 1);
        }else {
            int changePos = read<int>(),value = read<int>();
            lct.cut(changePos,values[changePos]);
            int distPos = changePos + value;
            if(distPos > n) distPos = n;
            lct.link(changePos,distPos);
            values[changePos] = distPos;
        }
    }
    return 0;
}
