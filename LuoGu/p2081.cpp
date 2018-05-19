#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#include <utility>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXM = MAXN * 2;
const int MAX_RING_SIZE = 22;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct List {
    int values[MAX_RING_SIZE],size;

    List() : size(0) { }

    void push(int value) {
        values[size++] = value;
    }

    int getNextPos(int pos) {
        int result = pos + 1;
        if(result == size) result = 0;
        return result;
    }

    int getPrevPos(int pos) {
        int result = pos - 1;
        if(result == -1) result = size - 1;
        return result;
    }
} list;

struct Graph {
    struct Edge {
        int next,to,weight;
    };
    Edge edges[MAXM];
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

    void addTwoEdges(int u,int v,int w) {
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
} graph;

int sizes[MAXN];
bool visit[MAXN];
double down[MAXN],up[MAXN];

void getDown(int now,int father) {
    sizes[now] = 0;
    down[now] = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to]) continue;
        sizes[now]++;
        getDown(tmpEdge.to,now);
        down[now] += tmpEdge.weight + down[tmpEdge.to];
    }
    if(sizes[now] != 0) {
        down[now] /= sizes[now];
    }
}

double result = 0;

void getUp(int now,int father,int fatherSize) {
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father || visit[tmpEdge.to]) continue;
        double tmpValue = down[now] * sizes[now] - tmpEdge.weight - down[tmpEdge.to] + up[now] * fatherSize;
        int turnSize = sizes[now] - 1 + fatherSize;
        if(turnSize == 0) turnSize = 1;
        up[tmpEdge.to] = tmpValue / turnSize;
        up[tmpEdge.to] += tmpEdge.weight;
        getUp(tmpEdge.to,now,1);
    }
    double tmpValue = down[now] * sizes[now] + up[now] * fatherSize;
    int turnSize = sizes[now] + fatherSize;
    result += tmpValue / turnSize;
}

int dfn[MAXN],low[MAXN],nowTime,sccCnt;
bool inStk[MAXN];
stack<int> stk;
vector<int> sccs[MAXN];

void tarjan(int now,int father) {
    dfn[now] = ++nowTime;
    low[now] = nowTime;
    inStk[now] = true;
    stk.push(now);
    bool isSkipped = false;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father && !isSkipped) {
            isSkipped = true;
            continue;
        }
        if(!dfn[tmpEdge.to]) {
            tarjan(tmpEdge.to,now);
            low[now] = min(low[now],low[tmpEdge.to]);
        }else if(inStk[tmpEdge.to]) {
            low[now] = min(low[now],low[tmpEdge.to]);
        }
    }
    if(low[now] == dfn[now]) {
        int tmpValue;
        do {
            tmpValue = stk.top();
            stk.pop();
            inStk[tmpValue] = false;
            sccs[sccCnt].push_back(tmpValue);
        }while(tmpValue != now);
        sccCnt++;
    }
}

map<pair<int,int>,vector<int> > saveEdges;

int main() {
    int n = read<int>(),m = read<int>();
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>(),w = read<int>();
        graph.addTwoEdges(u,v,w);
        saveEdges[make_pair(u,v)].push_back(w);
        saveEdges[make_pair(v,u)].push_back(w);
    }
    if(m == n - 1) {
        getDown(1,0);
        getUp(1,0,0);
        printf("%lf\n",result / n);
        return 0;
    }
    tarjan(1,0);
    int ringSize = -1;
    for(int i = 0;i < sccCnt;i++) {
        if(sccs[i].size() == 1) continue;
        for(vector<int>::iterator it = sccs[i].begin();it != sccs[i].end();it++) {
            list.push(*it);
        }
        ringSize = static_cast<int>(sccs[i].size());
        break;
    }
    for(int i = 0;i < ringSize;i++) {
        int now = list.values[i],prev = list.values[list.getPrevPos(i)],next = list.values[list.getNextPos(i)];
        visit[prev] = true;
        visit[next] = true;
        getDown(now,0);
        visit[prev] = false;
        visit[next] = false;
        visit[now] = true;
        if(prev != next) {
            getDown(prev,0);
            double firstDown = down[prev],firstWeight = *saveEdges[make_pair(prev,now)].begin();
            getDown(next,0);
            double secondDown = down[next],secondWeight = *saveEdges[make_pair(now,next)].begin();
            up[now] = (firstDown + firstWeight + secondDown + secondWeight) / 2.00;
        }else {
            getDown(prev,0);
            int firstWeight = *saveEdges[make_pair(prev,now)].begin(),secondWeight = *(saveEdges[make_pair(prev,now)].begin() + 1);
            up[now] = down[prev] + (firstWeight + secondWeight) * 1.00 / 2.00;
        }
        visit[now] = false;
        visit[prev] = true;
        visit[next] = true;
        getUp(now,0,2);
        visit[prev] = false;
        visit[next] = false;
    }
    printf("%lf\n",result / n);
    return 0;
}
