#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAX_VAL_RANGE = 2e6;
const int MODDER = 1999993;
const int MAXN = 10010;
const int MAXM = 110;

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph;

struct HashTable {
    set<int> values;

    HashTable() {
        clear();
    }

    void insert(int value) {
        values.insert(value);
    }

    bool contains(int value) {
        return values.count(value) == 1;
    }

    void clear() {
        values.clear();
    }
} hashTable;

bool visit[MAXN];
int n,m,sizes[MAXN],tmp[MAXN],querys[MAXM],results[MAXN],nowIndex,nowTreeSize,root,rootWeight;

void getRoot(int now,int father) {
    sizes[now] = 1;
    int maxChildSize = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        getRoot(tmpEdge.to,now);
        maxChildSize = max(maxChildSize,sizes[tmpEdge.to]);
        sizes[now] += sizes[tmpEdge.to];
    }
    maxChildSize = max(maxChildSize,nowTreeSize - sizes[now]);
    if(rootWeight > maxChildSize) {
        root = now;
        rootWeight = maxChildSize;
    }
}

void getLength(int now,int father,int nowLength) {
    tmp[nowIndex++] = nowLength;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        getLength(tmpEdge.to,now,nowLength + tmpEdge.weight);
    }
}

void calc(int now,int initValue,int extraValue) {
    nowIndex = 0;
    getLength(now,0,0);
    hashTable.clear();
    for(int i = 0;i < nowIndex;i++) {
        int nowValue = tmp[i] + initValue;
        for(int j = 0;j < m;j++) {
            int needValue = querys[j] - nowValue;
            if(needValue >= 0) {
                bool flag = hashTable.contains(needValue);
                results[j] += extraValue * static_cast<int>(flag);
            }
        }
        hashTable.insert(nowValue);
    }
}

void solve(int now) {
    visit[now] = true;
    calc(now,0,1);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        calc(tmpEdge.to,tmpEdge.weight,-1);
        root = 0;
        rootWeight = MAXN;
        nowTreeSize = sizes[tmpEdge.to];
        getRoot(tmpEdge.to,0);
        solve(root);
    }
}

int main() {
    n = read<int>();
    m = read<int>();
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    nowTreeSize = n;
    for(int i = 0;i < m;i++) {
        querys[i] = read<int>();
    }
    root = 0;
    rootWeight = MAXN;
    getRoot(1,0);
    solve(root);
    for(int i = 0;i < m;i++) {
        if(results[i] > 0) {
            printf("AYE\n");
        }else {
            printf("NAY\n");
        }
    }
    return 0;
}
