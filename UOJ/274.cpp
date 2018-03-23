#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <utility>
#include <cstddef>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 0x3f3f3f3f;
const int BUFFER_SIZE = 6;
const char * OPT_FIND = "find";
const char * OPT_MOVE = "move";
const char * OPT_CHANGE = "change";

int getOperation(char *str) {
    if(strcmp(str,OPT_FIND) == 0) {
        return 0;
    }
    if(strcmp(str,OPT_MOVE) == 0) {
        return 1;
    }
    if(strcmp(str,OPT_CHANGE) == 0) {
        return 2;
    }
}

struct LCT {
    struct Node {
        Node *father,*ch[2];
        int id,t,l,sumL,minT,minId;
        bool lazy;

        Node(int id,int t,int l) : father(NULL) , id(id) , t(t) , l(l) , sumL(l) , minT(t), minId(id) , lazy(false) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    } **nodes;

    LCT(int size,int nodeSize) {
        nodes = new Node*[size];
        for(int i = 0;i < nodeSize;i++) {
            nodes[i] = new Node(i,INF,0);
        }
    }

    void insert(int id,int t,int l) {
        nodes[id] = new Node(id,t,l);
    }

    int getSumL(Node *now) {
        if(now == NULL) return 0;
        return now->sumL;
    }

    void updateInfo(Node *now) {
        if(now == NULL) return;
        now->minT = now->t;
        now->minId = now->id;
        if(now->ch[0] != NULL) {
            if(now->minT > now->ch[0]->minT) {
                now->minT = now->ch[0]->minT;
                now->minId = now->ch[0]->minId;
            }
        }
        if(now->ch[1] != NULL) {
            if(now->minT > now->ch[1]->minT) {
                now->minT = now->ch[1]->minT;
                now->minId = now->ch[1]->minId;
            }
        }
        now->sumL = getSumL(now->ch[0]) + getSumL(now->ch[1]) + now->l;
    }

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->lazy = !now->lazy;
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(!now->lazy) return;
        updateReverseTag(now->ch[0]);
        updateReverseTag(now->ch[1]);
        swap(now->ch[0],now->ch[1]);
        updateReverseTag(now);
    }

    bool isRoot(Node *now) {
        if(now == NULL) return true;
        if(now->father == NULL) return true;
        return now->father->ch[0] != now && now->father->ch[1] != now;
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
        int direction = father->ch[0] == now;
        now->father = anc;
        father->father = now;
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

    Node *findFather(int pos) {
        Node *now = nodes[pos];
        access(pos);
        splay(now);
        while(now->ch[0] != NULL) {
            now = now->ch[0];
        }
        return now;
    }

    bool isLinked(int u,int v) {
        return findFather(u) == findFather(v);
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

    void cut(int u,int v) {
        split(u,v);
        if(nodes[v]->ch[0] == nodes[u] && nodes[u]->ch[1] == NULL) {
            nodes[v]->ch[0] = NULL;
            updateInfo(nodes[v]);
            nodes[u]->father = NULL;
        }
    }

    pair<int,int> getMin(int u,int v) {
        split(u,v);
        return make_pair(nodes[v]->minId,nodes[v]->minT);
    }

    int getLength(int u,int v) {
        split(u,v);
        return nodes[v]->sumL;
    }

    void changeLength(int pos,int l) {
        split(pos,pos);
        nodes[pos]->l = l;
        updateInfo(nodes[pos]);
    }

};


struct BCS {
    int *father;

    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

};
int main() {
    int n = read<int>(),m = read<int>();
    LCT lct(n + m,n);
    char *buffer = new char[BUFFER_SIZE + 1];
    pair<int,int> *roads = new pair<int,int>[n + m];
    BCS bcset(n);
    for(int now = 0;now < m;now++) {
        scanf("%s",buffer);
        int opt = getOperation(buffer);
        switch(opt) {
            case 0: {
                int id = read<int>(),u = read<int>(),v = read<int>(),t = read<int>(),l = read<int>();
                id += n;
                lct.insert(id,t,l);
                roads[id] = make_pair(u,v);
                if(bcset.isLinked(u,v)) {
                    pair<int,int> tmpResult = lct.getMin(u,v);
                    if(tmpResult.second < t) {
                        pair<int,int> tmpValue = roads[tmpResult.first];
                        lct.cut(tmpValue.first,tmpResult.first);
                        lct.cut(tmpResult.first,tmpValue.second);
                        lct.link(u,id);
                        lct.link(id,v);
                    }
                }else {
                    lct.link(u,id);
                    lct.link(id,v);
                    bcset.merge(u,v);
                }
                break;
            }
            case 1: {
                int u = read<int>(),v = read<int>();
                if(!bcset.isLinked(u,v)) {
                    printf("%d\n",-1);
                }else {
                    printf("%d\n",lct.getLength(u,v));
                }
                break;
            }
            case 2: {
                int id = read<int>(),l = read<int>();
                id += n;
                lct.changeLength(id,l);
                break;
            }
        }
    }
    return 0;
}
