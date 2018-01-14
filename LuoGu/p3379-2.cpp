#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <='9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
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

struct ST {
    int **values,*compareVal;
    ST(int *val,int length,int *compareVal) : compareVal(compareVal) {
        values = new int*[length];
        int calLen = myLog2(length);
        for(int i = 0;i < length;i++) {
            values[i] = new int[calLen + 1];
            values[i][0] = val[i];
        }
        for(int j = 1;j <= calLen;j++) {
            for(int i = 0;i + (1 << j) - 1 < length;i++) {
                if(compareVal[values[i][j - 1]] <= compareVal[values[i + (1 << (j - 1))][j - 1]]) {
                    values[i][j] = values[i][j - 1];
                }else {
                    values[i][j] = values[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int query(int left,int right) {
        if(left > right) return -1;
        int logVal = myLog2(right - left + 1);
        if(compareVal[values[left][logVal]] <= compareVal[values[right - (1 << logVal) + 1][logVal]]) {
            return values[left][logVal];
        }else {
            return values[right - (1 << logVal) + 1][logVal];
        }
    }

    int myLog2(int val) {
        return static_cast<int>(log(static_cast<double>(val)) / log(2.0));
    }
};

void getSeq(int now,int father,int nowDepth,int &nowInsertPos,int *values,int *depth,Graph &graph,int *firstPos) {
    values[nowInsertPos] = now;
    if(firstPos[now] == -1) {
        firstPos[now] = nowInsertPos;
    }
    depth[now] = nowDepth;
    nowInsertPos++;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        getSeq(tmpEdge.to,now,nowDepth + 1,nowInsertPos,values,depth,graph,firstPos);
        values[nowInsertPos++] = now;
    }
}

int main() {
    int N = read<int>(),M = read<int>(),S = read<int>();
    S--;
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    int nowInsertPos = 0,*values = new int[2 * N - 1],*depth = new int[N],*firstPos = new int[N];
    memset(depth,-1,sizeof(int) * N);
    memset(firstPos,-1,sizeof(int) * N);
    getSeq(S,-1,0,nowInsertPos,values,depth,graph,firstPos);
    ST table(values,2 * N - 1,depth);
    while(M--) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        int queryU = firstPos[u],queryV = firstPos[v];
        if(queryU > queryV) swap(queryU,queryV);
        printf("%d\n",table.query(queryU,queryV) + 1);
    }
    return 0;
}


