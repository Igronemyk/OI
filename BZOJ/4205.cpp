#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int PRIMES[50] = {
    1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
    103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
    163, 167, 173, 179, 181, 191, 193, 197, 199
};
const int PRIME_COUNT = 46;
const int MAX_VAL_RANGE = 200;
const int MAX_NODE_SIZE = 1e5;
const int MAXM = 8e6;
const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Graph {
    struct Edge {
        int next,to,flow;
    };
    Edge edges[MAXM];
    int tot,heads[MAX_NODE_SIZE];

    Graph() : tot(0) {
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v,int flow) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        edges[tot].flow = flow;
        heads[u] = tot++;
    }

    void addTwoEdges(int u,int v,int flow) {
        addEdge(u,v,flow);
        addEdge(v,u,0);
    }
} graph;

vector<int> primes[MAX_VAL_RANGE + 1];

int N1,N2;

void init() {
    for(int i = 1;i <= MAX_VAL_RANGE;i++) {
        for(int j = 1;j <= PRIME_COUNT;j++) {
            if(i % PRIMES[j] == 0) {
                primes[i].push_back(j);
            }
        }
    }
}

int mapedIndex[3][MAX_VAL_RANGE + 1][MAX_VAL_RANGE + 1];

int mapIndex(int start) {
    for(int i = 0;i < 3;i++) {
        for(int j = 1;j <= PRIME_COUNT;j++) {
            for(int k = 1;k <= PRIME_COUNT;k++) {
                mapedIndex[i][j][k] = start++;
            }
        }
    }
    return start;
}

void link(int nowIndex,int sign,int value1,int value2) {
    for(vector<int>::iterator it1 = primes[value1].begin();it1 != primes[value1].end();it1++) {
        for(vector<int>::iterator it2 = primes[value2].begin();it2 != primes[value2].end();it2++) {
            graph.addTwoEdges(sign,mapedIndex[nowIndex][*it1][*it2],1);
        }
    }
}

void link1(int nowIndex,int sign,int value1,int value2) {
    for(vector<int>::iterator it1 = primes[value1].begin();it1 != primes[value1].end();it1++) {
        for(vector<int>::iterator it2 = primes[value2].begin();it2 != primes[value2].end();it2++) {
            graph.addTwoEdges(mapedIndex[nowIndex][*it1][*it2],sign,1);
        }
    }
}

namespace Dinic {
    int S,T,step[MAX_NODE_SIZE],head[MAX_NODE_SIZE];

    bool bfs() {
        queue<int> que;
        que.push(S);
        memset(step,-1,sizeof(step));
        step[S] = 0;
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
                Graph::Edge &tmpEdge = graph.edges[i];
                if(tmpEdge.flow <= 0 || step[tmpEdge.to] != -1) continue;
                step[tmpEdge.to] = step[now] + 1;
                if(tmpEdge.to == T) return true;
                que.push(tmpEdge.to);
            }
        }
        return false;
    }

    int dfs(int now,int limit) {
        if(limit == 0) return 0;
        if(now == T) return limit;
        int result = 0;
        for(int &i = head[now];i != -1;i = graph.edges[i].next) {
            Graph::Edge &tmpEdge = graph.edges[i];
            if(tmpEdge.flow <= 0 || step[tmpEdge.to] != step[now] + 1) continue;
            int tmpResult = dfs(tmpEdge.to,min(limit,tmpEdge.flow));
            limit -= tmpResult;
            result += tmpResult;
            tmpEdge.flow -= tmpResult;
            graph.edges[i ^ 1].flow += tmpResult;
            if(limit == 0) break;
        }
        if(result == 0) {
            step[now] = -1;
        }
        return result;
    }

    int maxFlow(int S,int T) {
        Dinic::S = S;
        Dinic::T = T;
        int result = 0;
        while(bfs()) {
            memcpy(head,graph.heads,sizeof(head));
            result += dfs(S,INF);
        }
        return result;
    }
}

int main() {
    init();
    N1 = read<int>(); N2 = read<int>();
    int S = 0,T = mapIndex(N1 + N2 + 1);
    for(int i = 1;i <= N1;i++) {
        int a = read<int>(),b = read<int>(),c = read<int>();
        graph.addTwoEdges(S,i,1);
        link(0,i,a,b);
        link(1,i,b,c);
        link(2,i,c,a);
    }
    for(int i = 1;i <= N2;i++) {
        int a = read<int>(),b = read<int>(),c = read<int>();
        graph.addTwoEdges(i + N1,T,1);
        link1(0,i + N1,a,b);
        link1(1,i + N1,b,c);
        link1(2,i + N1,c,a);
    }
    printf("%d\n",Dinic::maxFlow(S,T));
    return 0;
}
