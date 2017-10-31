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

template<typename T>
struct Stack {
    T *values;
    int tail;
    Stack(int size) {
        values = new T[size];
        tail = 0;
    }

    void pop() {
        if(tail != 0) tail--;
    }

    void push(T val) {
        values[tail++] = val;
    }

    T top() {
        return values[tail - 1];
    }

    bool isEmpty() {
        return tail == 0;
    }

    int size() {
        return tail;
    }
};

template<typename T>
struct Queue {
    T *values;
    int head,tail;
    Queue(int size) {
        values = new T[size];
        head = 0;
        tail = 0;
    }

    T front() {
        return values[head];
    }

    void push(T val) {
        values[tail++] = val;
    }

    void pop() {
        if(head != tail) head++;
    }

    bool isEmpty() {
        return head == tail;
    }

    int size() {
        return tail - head;
    }

};

struct Graph {
    struct Edge {
        int next,to;
    } *edges;
    int tot,*heads;

    Graph(int edgeCount,int nodeCount) {
        edges = new Edge[edgeCount];
        heads = new int[nodeCount];
        memset(heads,-1,sizeof(int) * nodeCount);
        tot = 0;
    }

    void addEdge(int u,int v) {
        edges[tot].next = heads[u];
        edges[tot].to = v;
        heads[u] = tot++;
    }
};


void Tarjan(int now,int &nowTime,int &nowId,int *dfn,int *low,int *id,Stack<int> *stk,Graph *graph,bool *inStack) {
    dfn[now] = nowTime;
    low[now] = nowTime++;
    inStack[now] = true;
    stk->push(now);
    for(int i = graph->heads[now];i != -1;i = graph->edges[i].next) {
        Graph::Edge &tmpEdge = graph->edges[i];
        if(dfn[tmpEdge.to] == -1) {
            Tarjan(tmpEdge.to,nowTime,nowId,dfn,low,id,stk,graph,inStack);
            low[now] = min(low[now],low[tmpEdge.to]);
        }else if(inStack[tmpEdge.to]) {
            low[now] = min(low[now],dfn[tmpEdge.to]);
        }
    }
    if(low[now] == dfn[now]) {
        int tmpValue;
        do {
            tmpValue = stk->top();
            stk->pop();
            id[tmpValue] = nowId;
            inStack[tmpValue] = false;
        }while(tmpValue != now);
        nowId++;
    }
}


int main() {
    int n = read<int>(),m = read<int>(),*weight = new int[n];
    for(int i = 0;i < n;i++) {
        weight[i] = read<int>();
    }
    Graph *oldGraph = new Graph(m,n);
    for(int i = 0;i < m;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        oldGraph->addEdge(u,v);
    }
    int *dfn = new int[n],*low = new int[n],*id = new int[n],nowTime = 0,nowId = 0;
    bool *inStack = new bool[n];
    Stack<int> *stk = new Stack<int>(n);
    memset(dfn,-1,sizeof(int) * n);
    memset(low,-1,sizeof(int) * n);
    memset(id,-1,sizeof(int) * n);
    memset(inStack,false,sizeof(bool) * n);
    for(int i = 0;i < n;i++) {
        if(id[i] == -1) {
            Tarjan(i,nowTime,nowId,dfn,low,id,stk,oldGraph,inStack);
        }
    }
    Graph *newGraph = new Graph(m,nowId);
    int *newWeight = new int[nowId];
    bool *isRootNode = new bool[nowId];
    memset(newWeight,0,sizeof(int) * nowId);
    memset(isRootNode,true,sizeof(bool) * nowId);
    for(int i = 0;i < n;i++) {
        newWeight[id[i]] += weight[i];
        for(int j = oldGraph->heads[i];j != -1;j = oldGraph->edges[j].next) {
            Graph::Edge &tmpEdge = oldGraph->edges[j];
            if(id[i] == id[tmpEdge.to]) continue;
            newGraph->addEdge(id[i],id[tmpEdge.to]);
            if(isRootNode[id[tmpEdge.to]]) {
                isRootNode[id[tmpEdge.to]] = false;
            }
        }
    }
    bool *vis = new bool[nowId];
    memset(vis,false,sizeof(bool) * nowId);
    int *dis = new int[nowId];
    memcpy(dis,newWeight,sizeof(int) * nowId);
    Queue<int> que(nowId * nowId);
    for(int i = 0;i < nowId;i++) {
        if(isRootNode[i]) {
            que.push(i);
            vis[i] = true;
        }
    }
    while(!que.isEmpty()) {
        int val = que.front();
        que.pop();
        vis[val] = false;
        for(int j = newGraph->heads[val];j != -1;j = newGraph->edges[j].next) {
            Graph::Edge &tmpEdge = newGraph->edges[j];
            if(dis[tmpEdge.to] < dis[val] + newWeight[tmpEdge.to]) {
                dis[tmpEdge.to] = dis[val] + newWeight[tmpEdge.to];
                if(!vis[tmpEdge.to]) {
                    vis[tmpEdge.to] = true;
                    que.push(tmpEdge.to);
                }
            }
        }
    }
    int result = 0;
    for(int i = 0;i < nowId;i++) {
        result = max(result,dis[i]);
    }
    printf("%d\n",result);
    return 0;
}
