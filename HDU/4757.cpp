#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_TRIE_NODE_SIZE = 2300010;
const int MAX_BIT_SIZE = 16;
const int MAXN = 100010;
const int MAX_DEPTH = 22;

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
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }

    void clear() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }
} graph;

struct TrieNode {
    int ch[2],cnt;
} tn[MAX_TRIE_NODE_SIZE];

int trieSize = 0;

struct Trie {
    int root;

    static int newNode() {
        ++trieSize;
        tn[trieSize].ch[0] = 0;
        tn[trieSize].ch[1] = 0;
        tn[trieSize].cnt = 0;
        return trieSize;
    }

    static int newNode(int nodeSign) {
        ++trieSize;
        tn[trieSize].ch[0] = tn[nodeSign].ch[0];
        tn[trieSize].ch[1] = tn[nodeSign].ch[1];
        tn[trieSize].cnt = tn[nodeSign].cnt;
        return trieSize;
    }

    void insert(int value) {
        int now = root;
        for(int i = MAX_BIT_SIZE;i >= 0;i--) {
            bool index = ((1 << i) & value) != 0;
            if(tn[now].ch[index] == 0) {
                tn[now].ch[index] = newNode();
            }else {
                tn[now].ch[index] = newNode(tn[now].ch[index]);
            }
            now = tn[now].ch[index];
            tn[now].cnt++;
        }
    }

    static int getMaxXorValue(Trie u,Trie v,Trie lca,Trie lcaFa,int value) {
        return getMaxXorValue(u.root,v.root,lca.root,lcaFa.root,value);
    }

    static int getMaxXorValue(int u,int v,int lca,int lcaFa,int value) {
        int result = 0;
        for(int i = MAX_BIT_SIZE;i >= 0;i--) {
            bool index = ((1 << i) & value) != 0;
            int cnt = tn[tn[u].ch[!index]].cnt + tn[tn[v].ch[!index]].cnt - tn[tn[lca].ch[!index]].cnt - tn[tn[lcaFa].ch[!index]].cnt;
            if(cnt == 0) {
                u = tn[u].ch[index];
                v = tn[v].ch[index];
                lca = tn[lca].ch[index];
                lcaFa = tn[lcaFa].ch[index];
                if(index == 1) {
                    result |= (1 << i);
                }
            }else {
                u = tn[u].ch[!index];
                v = tn[v].ch[!index];
                lca = tn[lca].ch[!index];
                lcaFa = tn[lcaFa].ch[!index];
                if(index == 0) {
                    result |= (1 << i);
                }
            }
        }
        return result;
    }

};

Trie tries[MAXN];
int n,m,values[MAXN],depth[MAXN],father[MAXN][MAX_DEPTH + 1];

void dfs(int now,int father) {
    depth[now] = depth[father] + 1;
    ::father[now][0] = father;
    tries[now].root = Trie::newNode(tries[father].root);
    tries[now].insert(values[now]);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now);
    }
}

void init() {
    for(int i = 1;i <= MAX_DEPTH;i++) {
        for(int j = 1;j <= n;j++) {
            father[j][i] = father[father[j][i - 1]][i - 1];
        }
    }
}

int getLCA(int u,int v) {
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depth[father[u][i]] >= depth[v]) {
            u = father[u][i];
        }
    }
    if(u == v) return u;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(father[u][i] != father[v][i]) {
            u = father[u][i];
            v = father[v][i];
        }
    }
    return father[u][0];
}

int main() {
    while(~scanf("%d%d",&n,&m)) {
        trieSize = 0;
        memset(father,0,sizeof(father));
        memset(values,0,sizeof(values));
        memset(depth,0,sizeof(depth));
        graph.clear();
        for(int i = 1;i <= n;i++) {
            values[i] = read<int>();
        }
        for(int i = 0;i < n - 1;i++) {
            int u = read<int>(),v = read<int>();
            graph.addEdge(u,v);
            graph.addEdge(v,u);
        }
        tries[0].root = Trie::newNode();
        dfs(1,0);
        init();
        while(m--) {
            int x = read<int>(),y = read<int>(),z = read<int>();
            int lca = getLCA(x,y);
            printf("%d\n",z ^ Trie::getMaxXorValue(tries[x],tries[y],tries[lca],tries[father[lca][0]],z));
        }
    }
    return 0;
}
