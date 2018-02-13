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

    void push(T value) {
        values[tail++] = value;
    }

    T top() {
        return values[tail - 1];
    }

    int size() {
        return tail;
    }

    bool empty() {
        return tail == 0;
    }
};

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
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
};

void dfs(int now,int father,Graph &graph,Stack<int> &stk,int &nowIndex,int *indexSign,int *capital,int &limit) {
    int nowSize = stk.size();
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        dfs(tmpEdge.to,now,graph,stk,nowIndex,indexSign,capital,limit);
        if(stk.size() - nowSize >= limit) {
            while(stk.size() > nowSize) {
                int tmpValue = stk.top();
                stk.pop();
                indexSign[tmpValue] = nowIndex;
            }
            capital[nowIndex] = now;
            nowIndex++;
        }
    }
    stk.push(now);
}

int main() {
    int N = read<int>(),B = read<int>();
    Graph graph((N - 1) * 2,N);
    for(int i = 0;i < N - 1;i++) {
        int u = read<int>(),v = read<int>();
        u--; v--;
        graph.addEdge(u,v);
        graph.addEdge(v,u);
    }
    Stack<int> stk(N);
    int nowIndex = 0,*indexSign = new int[N],*capital = new int[N];
    dfs(0,-1,graph,stk,nowIndex,indexSign,capital,B);
    while(!stk.empty()) {
        int tmpValue = stk.top();
        stk.pop();
        indexSign[tmpValue] = nowIndex - 1;
    }
    printf("%d\n",nowIndex);
    for(int i = 0;i < N;i++) {
        printf("%d",indexSign[i] + 1);
        if(i != N - 1) printf(" ");
    }
    printf("\n");
    for(int i = 0;i < nowIndex;i++) {
        printf("%d",capital[i] + 1);
        if(i != nowIndex - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
