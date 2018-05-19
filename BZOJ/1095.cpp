#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;
const int MAXM = 500010;
const int MAX_DEPTH = 17;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-')  f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
} graph,newGraph;

int N,fathers[MAXN][MAX_DEPTH + 1],depths[MAXN],sizes[MAXN],newFathers[MAXN],root,nowRootSize,nowTreeSize,newRoot;
bool visit[MAXN],isDark[MAXN];
multiset<int> disValues[MAXN],topValues[MAXN],results;

int getLCA(int u,int v) {
    if(u == v) return u;
    if(depths[u] < depths[v]) {
        swap(u,v);
    }
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(depths[fathers[u][i]] >= depths[v]) {
            u = fathers[u][i];
        }
    }
    if(u == v) return u;
    for(int i = MAX_DEPTH;i >= 0;i--) {
        if(fathers[u][i] != fathers[v][i]) {
            u = fathers[u][i];
            v = fathers[v][i];
        }
    }
    return fathers[u][0];
}

int getDis(int u,int v) {
    return depths[u] + depths[v] - 2 * depths[getLCA(u,v)];
}

void getInfo(int now,int father) {
    depths[now] = depths[father] + 1;
    fathers[now][0] = father;
    sizes[now] = 1;
    for(int i = 1;i <= MAX_DEPTH;i++) {
        fathers[now][i] = fathers[fathers[now][i -1]][i - 1];
    }
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getInfo(tmpEdge.to,now);
        sizes[now] += sizes[tmpEdge.to];
    }
}

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
    if(nowRootSize > maxChildSize) {
        nowRootSize = maxChildSize;
        root = now;
    }
}

void buildTree(int now) {
    visit[now] = true;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        root = 0;
        nowRootSize = MAXN;
        nowTreeSize = sizes[tmpEdge.to];
        getRoot(tmpEdge.to,0);
        newFathers[root] = now;
        newGraph.addEdge(now,root);    
        buildTree(root);
    }
}

void calcDis(int now,int nowDis,const int &nowDist,const int &nowFrom) {
    if(isDark[now]) {
        disValues[nowDist].insert(nowDis);
    }
    for(int i = newGraph.heads[now];i != -1;i = newGraph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        calcDis(tmpEdge.to,getDis(nowFrom,tmpEdge.to),nowDist,nowFrom);
    }
}

void init(int now) {
    for(int i = newGraph.heads[now];i != -1;i = newGraph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        calcDis(tmpEdge.to,getDis(now,tmpEdge.to),tmpEdge.to,now);
        init(tmpEdge.to);
        if(disValues[tmpEdge.to].size() != 0) {
            topValues[now].insert(*disValues[tmpEdge.to].rbegin());
        }
    }
    if(topValues[now].size() >= 2) {
        results.insert(*(++topValues[now].rbegin()) + *(topValues[now].rbegin()));         
    }else if(topValues[now].size() == 1 && isDark[now]) {
        results.insert(*topValues[now].rbegin());
    }
}

void turnUp(int pos) {
    int now = pos;
    if(topValues[now].size() == 1) {
        results.erase(results.lower_bound(*topValues[now].rbegin()));
    }
    while(pos != newRoot) {
        multiset<int> &faT = topValues[newFathers[pos]],&posD = disValues[pos];
        if(faT.size() >= 2) {
            results.erase(results.lower_bound(*(++faT.rbegin()) + *(faT.rbegin())));
        }else if(faT.size() == 1 && isDark[newFathers[pos]]) {
            results.erase(results.lower_bound(*faT.rbegin()));
        }
        faT.erase(faT.lower_bound(*posD.rbegin()));
        posD.erase(posD.lower_bound(getDis(newFathers[pos],now)));
        if(posD.size() != 0) {
            faT.insert(*posD.rbegin());
        }
        if(faT.size() >= 2) {
            results.insert(*(++faT.rbegin()) + *(faT.rbegin()));
        }else if(faT.size() == 1 && isDark[newFathers[pos]]) {
            results.insert(*faT.rbegin());
        }
        pos = newFathers[pos];
    }
}

void turnDown(int pos) {
    int now = pos;
    if(topValues[now].size() == 1) {
        results.insert(*topValues[now].rbegin());
    }
    while(pos != newRoot) {
        multiset<int> &faT = topValues[newFathers[pos]],&posD = disValues[pos];
        if(faT.size() >= 2) {
            results.erase(results.lower_bound(*(++faT.rbegin()) + *(faT.rbegin())));
        }else if(faT.size() == 1 && isDark[newFathers[pos]]) {
            results.erase(results.lower_bound(*faT.rbegin()));
        }
        if(posD.size() != 0) {
            faT.erase(faT.lower_bound(*posD.rbegin()));
        }
        posD.insert(getDis(newFathers[pos],now));
        faT.insert(*posD.rbegin());
        if(faT.size() >= 2) {
            results.insert(*(++faT.rbegin()) + *(faT.rbegin()));
        }else if(faT.size() == 1 && isDark[newFathers[pos]]) {
            results.insert(*faT.rbegin());        
        }
        pos = newFathers[pos];
    }
}

int main() {
    N = read<int>();
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>(); 
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    getInfo(1,0);
    root = 0;
    nowRootSize = MAXN;
    nowTreeSize = sizes[1];
    getRoot(1,0);
    newRoot = root;
    buildTree(root);
    memset(isDark,1,sizeof(isDark));
    init(newRoot);
    int Q = read<int>(),cnt = N;
    char *buffer = new char[2];
    while(Q--) {
        scanf("%s",buffer);
        if(buffer[0] == 'G') {
            if(cnt == 1) {
                printf("-1\n");
            }else if(cnt == 0) {
                printf("0\n");
            }else {
                printf("%d\n",*results.rbegin());
            }
            continue;
        }
        int sign = read<int>();
        if(isDark[sign]) {
            turnUp(sign);
            cnt--;
        }else {
            turnDown(sign);
            cnt++;
        }
        isDark[sign] = !isDark[sign];
    }
    return 0;
}

