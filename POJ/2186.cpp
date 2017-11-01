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

struct Stack {
    int *values,tail;
    Stack(int size) {
        values = new int[size];
        tail = 0;
    }

    void push(int value) {
        values[tail++] = value;
    }

    int top() {
        return values[tail - 1];
    }

    void pop() {
        tail--;
    }

    int size() {
        return tail;
    }

    bool isEmpty() {
        return tail == 0;
    }
};


struct Graph {
    struct Edge {
        int next,to;
    } *edges;
    int tot,*heads,nodeSize;

    Graph(int edgeSize,int nodeSize) : nodeSize(nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void reInit() {
        tot = 0;
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

void Tarjan(int now,int &nowTime,int &nowId,int *dfn,int *low,int *id,Graph &graph,Stack &stk,bool *inStack) {
    low[now] = nowTime;
    dfn[now] = nowTime++;
    inStack[now] = true;
    stk.push(now);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(dfn[tmpEdge.to] == -1) {
            Tarjan(tmpEdge.to,nowTime,nowId,dfn,low,id,graph,stk,inStack);
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
            id[tmpValue] = nowId;
        }while(tmpValue != now);
        nowId++;
    }
}

int main() {
    int N,M;
    while(~scanf("%d%d",&N,&M)) {
        Graph oldGraph(M,N);
        for(int i = 0;i < M;i++) {
            int u = read<int>(),v = read<int>();
            u--; v--;
            oldGraph.addEdge(u,v);
        }
        int *dfn = new int[N],*low = new int[N],*id = new int[N],nowTime = 0,nowId = 0;
        memset(dfn,-1,sizeof(int) * N);
        memset(low,-1,sizeof(int) * N);
        memset(id,-1,sizeof(int) * N);
        Stack stk(N);
        bool *inStack = new bool[N];
        memset(inStack,false,sizeof(bool) * N);
        for(int i = 0;i < N;i++) {
            if(dfn[i] == -1) {
                Tarjan(i,nowTime,nowId,dfn,low,id,oldGraph,stk,inStack);
            }
        }
        int *countSum = new int[nowId];
        bool *isFinish = new bool[nowId];
        memset(countSum,0,sizeof(int) * nowId);
        memset(isFinish,true,sizeof(bool) * nowId);
        for(int i = 0;i < N;i++) {
            countSum[id[i]]++;
            for(int j = oldGraph.heads[i];j != -1;j = oldGraph.edges[j].next) {
                Graph::Edge &tmpEdge = oldGraph.edges[j];
                if(id[i] == id[tmpEdge.to]) continue;
                isFinish[id[i]] = false;
            }
        }
        int countZero = 0,selectPoint = -1;
        for(int i = 0;i < nowId;i++) {
            if(isFinish[i]) {
                countZero++;
                selectPoint = i;
            }
        }
        if(countZero > 1) {
            printf("0\n");
        }else {
            printf("%d\n",countSum[selectPoint]);
        }
    }
    return 0;
}
