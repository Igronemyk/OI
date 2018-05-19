#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;
const int MAX_DEPTH = 18;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXN * 2];
    int tot,heads[MAXN];

    Graph() : tot(0) { 
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int w) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].weight = w;
        heads[u] = tot++;
    }
} graph,newGraph;

int valueLog2[MAXN * 2],dfn[MAXN],sizes[MAXN],dis[MAXN],fathers[MAXN],newRoot;

long long sumDis1[MAXN],sumDis2[MAXN],sumVal1[MAXN],sumVal2[MAXN];

bool visit[MAXN];

struct ST {
    int values[MAXN * 2][MAX_DEPTH + 1],length;

    ST() : length(0) {
        memset(values,0,sizeof(values));
    }

    void build() {
        int calLength = valueLog2[length];
        for(int j = 1;j <= calLength;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                values[i][j] = min(values[i][j - 1],values[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int left,int right) {
        if(left > right) swap(left,right);
        int calLength = valueLog2[right - left + 1];
        return min(values[left][calLength],values[right - (1 << calLength) + 1][calLength]);
    }
} st;


void init() {
    for(int i = 2;i < MAXN * 2;i++) {
        valueLog2[i] = valueLog2[i >> 1] + 1;
    }
}

void getInfo(int now,int father) {
    sizes[now] = 1;
    dfn[now] = st.length;
    st.values[st.length++][0] = dis[now];
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dis[tmpEdge.to] = dis[now] + tmpEdge.weight;
        getInfo(tmpEdge.to,now);
        st.values[st.length++][0] = dis[now];
        sizes[now] += sizes[tmpEdge.to];
    }
}

void getCenter(int now,int father,const int nowTreeSize,int &nowRoot,int &nowRootSize) {
    int maxChildSize = 1;
    sizes[now] = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        getCenter(tmpEdge.to,now,nowTreeSize,nowRoot,nowRootSize);
        maxChildSize = max(maxChildSize,sizes[tmpEdge.to]);
        sizes[now] += sizes[tmpEdge.to];
    }
    maxChildSize = max(maxChildSize,nowTreeSize - sizes[now]);
    if(nowRootSize > maxChildSize) {
        nowRootSize = maxChildSize;
        nowRoot = now;
    }
}

void getSize(int now,int father) {
    sizes[now] = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to] || tmpEdge.to == father) continue;
        getSize(tmpEdge.to,now);
        sizes[now] += sizes[tmpEdge.to];
    }
}

int build(int now) {
    int root = 0,rootSize = MAXN;
    getSize(now,0);
    getCenter(now,0,sizes[now],root,rootSize);
    visit[root] = true;
    for(int i = graph.heads[root];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(visit[tmpEdge.to]) continue;
        int to = build(tmpEdge.to);
        fathers[to] = root;
        newGraph.addEdge(root,to,tmpEdge.to);
    }
    return root;
}

int getDis(int u,int v) {
    return dis[u] + dis[v] - 2 * st.query(dfn[u],dfn[v]);
}

void change(int u,int e) {
    sumVal1[u] += e;
    int now = u;
    while(fathers[now] != 0) {
        int dis = getDis(fathers[now],u);
        sumDis1[fathers[now]] += dis * 1LL * e;
        sumDis2[now] += dis * 1LL * e;
        sumVal1[fathers[now]] += e;
        sumVal2[now] += e;
        now = fathers[now];
    }
}

long long calc(int pos) {
    long long result = sumDis1[pos];
    int now = pos;
    while(fathers[now] != 0) {
        int dis = getDis(fathers[now],pos);
        result += sumDis1[fathers[now]] - sumDis2[now];
        result += dis * 1LL * (sumVal1[fathers[now]] - sumVal2[now]);
        now = fathers[now];
    }
    return result;
}

long long getResult(int now) {
    long long tmpResult = calc(now);
    for(int i = newGraph.heads[now];i != -1;i = newGraph.edges[i].next) {
        Graph::Edge &tmpEdge = newGraph.edges[i];
        long long tempValue = calc(tmpEdge.weight);
        if(tempValue < tmpResult) {
            return getResult(tmpEdge.to);
        }
    }
    return tmpResult;
}

int main() {
    init();
    int n = read<int>(),Q = read<int>();
    for(int i = 0;i < n - 1;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addEdge(u,v,w);
        graph.addEdge(v,u,w);
    }
    getInfo(1,0);
    st.build();
    newRoot = build(1);
    while(Q--) {
        int u = read<int>(),e = read<int>();
        change(u,e);
        printf("%lld\n",getResult(newRoot));
    }
    return 0;
}
