#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;
const char *OPT_CHANGE = "UPDATE";
const char *OPT_QMAX = "MAX";
const char *OPT_QSUM = "SUM";

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    } *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }

};

struct LCT {
    struct Node {
        Node *father,*childs[2];
        int value,sumValue,maxValue,reverseTag;

        Node() : father(NULL) , value(-1) , sumValue(-1) , maxValue(-1) , reverseTag(-1) { }
        Node(int value) : father(NULL) , value(value) , sumValue(value) , maxValue(value) , reverseTag(0) { }
    } **nodes;

    int nowSize;

    LCT() : nodes(NULL) { }

    LCT(int size) : nowSize(0) {
        nodes = new Node*[size];
    }

    void insert(int value) {
        nodes[nowSize++] = new Node(value);
    }

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->childs[0] != now && now->father->childs[1] != now;
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(!isRoot(father)) {
            anc->childs[anc->childs[1] == father] = now;
        }
        int direction = father->childs[0] == now;
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

    void updateReverseTag(Node *now) {
        if(now == NULL) return;
        now->reverseTag ^= 1;
    }

    void pushDown(Node *now) {
        if(now == NULL) return;
        if(now->reverseTag == 0) return;
        updateReverseTag(now->childs[0]);
        updateReverseTag(now->childs[1]);
        swap(now->childs[0],now->childs[1]);
        updateReverseTag(now);
    }

    void updateInfo(Node *now) {
        now->sumValue = getSumValue(now->childs[0]) + getSumValue(now->childs[1]) + now->value;
        now->maxValue = max(max(getMaxValue(now->childs[0]),getMaxValue(now->childs[1])),now->value);
    }

    int getSumValue(Node *now) {
        if(now == NULL) return 0;
        return now->sumValue;
    }

    int getMaxValue(Node *now) {
        if(now == NULL) return -INF;
        return now->maxValue;
    }

    void access(Node *now) {
        Node *prev = NULL;
        for(Node *doing = now;doing != NULL;doing = doing->father) {
            splay(doing);
            doing->childs[1] = prev;
            updateInfo(doing);
            prev = doing;
        }
    }

    void makeRoot(Node *now) {
        access(now);
        splay(now);
        updateReverseTag(now);
    }

    void link(int x,int y) {
        Node *nodeX = nodes[x],*nodeY = nodes[y];
        makeRoot(nodeX);
        nodeX->father = nodeY;
    }

    void changeValue(int pos,int value) {
        Node *now = nodes[pos];
        makeRoot(now);
        now->value = value;
        updateInfo(now);
    }

    int getSumValue(int x,int y) {
        Node *nodeX = nodes[x],*nodeY = nodes[y];
        makeRoot(nodeX);
        access(nodeY);
        splay(nodeY);
        return nodeY->sumValue;
    }

    int getMaxValue(int x,int y) {
        Node *nodeX = nodes[x],*nodeY = nodes[y];
        makeRoot(nodeX);
        access(nodeY);
        splay(nodeY);
        return nodeY->maxValue;
    }

};

void dfs(int now,int father,Graph &graph,LCT &lct) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now,graph,lct);
        lct.link(now,tmpEdge.to);
    }
}

int main() {
    int n = read<int>(),m = read<int>();
    Graph graph((n - 1) * 2,n);
    LCT lct(n);
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        lct.insert(tmpValue);
    }
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    dfs(0,-1,graph,lct);
    char *buffer = new char[7];
    while(m--) {
        scanf("%s",buffer);
        if(strcmp(buffer,OPT_CHANGE) == 0) {
            int u = read<int>(),value = read<int>();
            u--;
            lct.changeValue(u,value);
        }else if(strcmp(buffer,OPT_QMAX) == 0) {
            int u = read<int>(),v = read<int>();
            u--; v--;
            printf("%d\n",lct.getMaxValue(u,v));
        }else if(strcmp(buffer,OPT_QSUM) == 0) {
            int u = read<int>(),v = read<int>();
            u--; v--;
            printf("%d\n",lct.getSumValue(u,v));
        }
    }

    return 0;
}
