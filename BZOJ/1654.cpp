#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

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
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
};

template<typename T>
struct Stack {
    T *values;
    int tail;
    Stack(int size) {
        values = new T[size];
        tail = 0;
    }

    void push(T value) {
        values[tail++] = value;
    }

    T top() {
        return values[tail - 1];
    }

    void pop() {
        tail--;
    }

    bool empty() {
        return tail == 0;
    }
};

void tarjan(int now,Graph &graph,int *dfn,int *low,bool *inStack,int &nowTime,int &nowIndex,Stack<int> &stk) {
    dfn[now] = nowTime++;
    low[now] = dfn[now];
    inStack[now] = true;
    stk.push(now);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dfn[tmpEdge.to] == -1) {
            tarjan(tmpEdge.to,graph,dfn,low,inStack,nowTime,nowIndex,stk);
            low[now] = min(low[now],low[tmpEdge.to]);
        }else if(inStack[tmpEdge.to]) {
            low[now] = min(low[now],low[tmpEdge.to]);
        }
    }
    if(low[now] == dfn[now]) {
        int tmpValue,cnt = 0;
        do {
            cnt++;
            tmpValue = stk.top();
            stk.pop();
            inStack[tmpValue] = false;
        }while(tmpValue != now);
        if(cnt > 1) nowIndex++;
    }
}

int main() {
    int N = read<int>(),M = read<int>();
    Graph graph(M,N);
    for(int i = 0;i < M;i++) {
        int A = read<int>(),B = read<int>();
        A--; B--;
        graph.addEdge(A,B);
    }
    int nowTime = 0,nowIndex = 0,*dfn = new int[N],*low = new int[N];
    bool *inStack = new bool[N];
    Stack<int> stk(N);
    memset(dfn,-1,sizeof(int) * N);
    memset(inStack,false,sizeof(bool) * N);
    for(int i = 0;i < N;i++) {
        if(dfn[i] == -1) {
            tarjan(i,graph,dfn,low,inStack,nowTime,nowIndex,stk);
        }
    }
    printf("%d\n",nowIndex);
    return 0;
}
