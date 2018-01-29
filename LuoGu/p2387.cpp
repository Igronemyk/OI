#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int MAX_LCT_NODE_SIZE = 150010;
const int MAX_VAL_RANGE = 50010;
const int INF = 0x3f3f3f3f;

typedef pair<pair<int,int>,pair<int,int> > Edge;

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
        int sign,maxPos,value;
        bool rev;

        Node(int sign,int value) : father(NULL) , sign(sign) , maxPos(sign) , value(value) , rev(false) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    } **nodes;

    LCT(int size,int *values) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) {
            nodes[i] = new Node(i,values[i]);
        }
    }

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->ch[0] != now && now->father->ch[1] != now;
    }

    void updateInfo(Node *now) {
        now->maxPos = now->sign;
        if(now->ch[0] != NULL && nodes[now->ch[0]->maxPos]->value > nodes[now->maxPos]->value) {
            now->maxPos = now->ch[0]->maxPos;
        }
        if(now->ch[1] != NULL && nodes[now->ch[1]->maxPos]->value > nodes[now->maxPos]->value) {
            now->maxPos = now->ch[1]->maxPos;
        }
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

    pair<int,int> getMax(int u,int v) {
        split(u,v);
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        return make_pair(nodeV->maxPos,nodes[nodeV->maxPos]->value);
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->ch[0]);
        printf("%d ",now->sign);
        print(now->ch[1]);
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

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
    }
};

bool comp(const Edge &e1,const Edge &e2) {
    return e1.second < e2.second;
}

int main() {
    int N = read<int>(),M = read<int>(),nodeSize = N + M,*values = new int[nodeSize];
    memset(values,0,sizeof(int) * nodeSize);
    Edge *edges = new Edge[M];
    for(int i = 0;i < M;i++) {
        int x = read<int>(),y = read<int>(),a = read<int>(),b = read<int>();
        x--; y--;
        edges[i] = make_pair(make_pair(x,y),make_pair(a,b));
    }
    sort(edges,edges + M,comp);
    for(int i = 0;i < M;i++) {
        values[i + N] = edges[i].second.second;
    }
    LCT lct(nodeSize,values);
    BCS bcset(N);
    int nowPos = 0,result = INF;
    for(int nowA = 1;nowA <= MAX_VAL_RANGE;nowA++) {
        while(nowPos < M && edges[nowPos].second.first == nowA) {
            Edge &tmpEdge = edges[nowPos];
            if(bcset.isLinked(tmpEdge.first.first,tmpEdge.first.second)) {
                pair<int,int> maxInfo = lct.getMax(tmpEdge.first.first,tmpEdge.first.second);
                if(maxInfo.second > tmpEdge.second.second) {
                    lct.cut(edges[maxInfo.first - N].first.first,maxInfo.first);
                    lct.cut(maxInfo.first,edges[maxInfo.first - N].first.second);
                    lct.link(tmpEdge.first.first,N + nowPos);
                    lct.link(N + nowPos,tmpEdge.first.second);
                }
            }else {
                lct.link(tmpEdge.first.first,N + nowPos);
                lct.link(N + nowPos,tmpEdge.first.second);
                bcset.merge(tmpEdge.first.first,tmpEdge.first.second);
            }
            nowPos++;
        }
        if(bcset.isLinked(0,N - 1)) {
            pair<int,int> maxInfo = lct.getMax(0,N - 1);
            result = min(result,nowA + maxInfo.second);
        }
    }
    if(result == INF) {
        printf("%d\n",-1);
    }else {
        printf("%d\n",result);
    }
    return 0;
}
