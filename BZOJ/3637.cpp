#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool *color;

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
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
        int size,virtualSize,sign;
        Node() : father(NULL) , size(-1) , virtualSize(-1) , sign(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(int sign) : father(NULL) , size(1) , virtualSize(0) , sign(sign) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

    } **nodes;

    LCT() : nodes(NULL) { }

    LCT(int size) {
        nodes = new Node*[size];
        for(int i = 0;i < size;i++) {
            nodes[i] = new Node(i);
        }
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
        int direction = father->childs[0] == now;
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

    void splay(Node *now) {
        if(now == NULL) return;
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

    void splay(Node *now,Node *dist) {
        if(now == NULL) return;
        while(now->father != dist) {
            Node *father = now->father,*anc = father->father;
            if(anc != dist) {
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

    bool isRoot(Node *now) {
        if(now->father == NULL) return true;
        return now->father->childs[0] != now && now->father->childs[1] != now;
    }

    void link(int u,int v) {
        if(v == -1) return;
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        splay(nodeU);
        access(nodeV);
        splay(nodeV);
        nodeU->father = nodeV;
        nodeV->virtualSize += nodeU->size;
        updateInfo(nodeV);
    }

    void cut(int u,int v) {
        if(v == -1) return;
        Node *nodeU = nodes[u],*nodeV = nodes[v];
        access(nodeU);
        splay(nodeV);
        splay(nodeU,nodeV);
        nodeV->childs[1] = NULL;
        nodeU->father = NULL;
        updateInfo(nodeV);
    }

    int getValue(int pos) {
        Node *now = nodes[pos];
        access(now);
        splay(now);
        Node *doing = now;
        while(doing->childs[0] != NULL) {
            doing = doing->childs[0];
        }
        splay(doing);
        if(color[doing->sign] == color[now->sign]) {
            return doing->size;
        }else {
            doing = doing->childs[1];
            while(doing->childs[0] != NULL) {
                doing = doing->childs[0];
            }
            access(doing);
            return doing->virtualSize + 1;
        }
    }

};



LCT *trees[2];

void dfs(int now,int nowFather,int *father,Graph &graph) {
    father[now] = nowFather;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == nowFather) continue;
        trees[1]->link(tmpEdge.to,now);
        dfs(tmpEdge.to,now,father,graph);
    }
}

int main() {
    int n = read<int>();
    Graph graph((n - 1) * 2,n);
    trees[0] = new LCT(n);
    trees[1] = new LCT(n);
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    int *father = new int[n];
    dfs(0,-1,father,graph);
    color = new bool[n];
    memset(color,true,sizeof(bool) * n);
    int m = read<int>();
    while(m--) {
        int opt = read<int>(),u = read<int>();
        u--;
        if(opt == 0) {
            printf("%d\n",trees[color[u]]->getValue(u));
        }else {
            trees[color[u]]->cut(u,father[u]);
            color[u] = !color[u];
            trees[color[u]]->link(u,father[u]);
        }
    }
    return 0;
}
