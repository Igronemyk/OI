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

    void pop() {
        tail--;
    }

    T top() {
        return values[tail - 1];
    }

    void push(T value) {
        values[tail++] = value;
    }

    bool empty() {
        return tail == 0;
    }
};

void tarjan(int now,Graph &graph,int *dfn,int *low,int *belong,bool *inStack,int &nowTime,int &nowIndex,Stack<int> &stk) {
    dfn[now] = nowTime++;
    low[now] = dfn[now];
    inStack[now] = true;
    stk.push(now);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dfn[tmpEdge.to] == -1) {
            tarjan(tmpEdge.to,graph,dfn,low,belong,inStack,nowTime,nowIndex,stk);
            low[now] = min(low[now],low[tmpEdge.to]);
        }else if(inStack[tmpEdge.to]) {
            low[now] = min(low[now],low[tmpEdge.to]);
        }
    }
    if(low[now] == dfn[now]) {
        int tmpValue;
        do {
            tmpValue = stk.top();
            stk.pop();
            inStack[tmpValue] = false;
            belong[tmpValue] = nowIndex;
        }while(tmpValue != now);
        nowIndex++;
    }
}


int main() {
    int n,m;
    while(~scanf("%d%d",&n,&m)) {
        int nodeSize = 2 * n;
        Graph graph(m * 2,nodeSize);
        for(int i = 0;i < m;i++) {
            int a1 = read<int>(),a2 = read<int>(),c1 = read<int>(),c2 = read<int>();
            graph.addEdge(2 * a1 + c1,2 * a2 + 1 - c2);
            graph.addEdge(2 * a2 + c2,2 * a1 + 1 - c1);
        }
        int *dfn = new int[nodeSize],*low = new int[nodeSize],*belong = new int[nodeSize],nowTime = 0,nowIndex = 0;
        bool *inStack = new bool[nodeSize];
        memset(dfn,-1,sizeof(int) * nodeSize);
        memset(inStack,false,sizeof(bool) * nodeSize);
        Stack<int> stk(nodeSize);
        for(int i = 0;i < nodeSize;i++) {
            if(dfn[i] == -1) {
                tarjan(i,graph,dfn,low,belong,inStack,nowTime,nowIndex,stk);
            }
        }
        bool flag = true;
        for(int i = 0;i < n;i++) {
            if(belong[i * 2] == belong[i * 2 + 1]) {
                flag = false;
                break;
            }
        }
        if(flag) {
            printf("YES\n");
        }else {
            printf("NO\n");
        }
    }
    return 0;
}
