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

struct LeftTree {
    struct Node {
        Node *ch[2];
        int dis,size;
        long long value,sumValue;

        Node(int value) : dis(0) , size(1) , value(value) , sumValue(value) { }
    };

    Node *root;

    LeftTree() : root(NULL) { }
    LeftTree(int value) : root(new Node(value)) { }

    int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    long long getSumValue(Node *now) {
        if(now == NULL) return 0;
        return now->sumValue;
    }

    long long getSumValue() {
        if(root == NULL) return 0;
        return root->sumValue;
    }

    int getSize() {
        if(root == NULL) return 0;
        return root->size;
    }

    void updateInfo(Node *now) {
        now->dis = now->ch[1] != NULL ? now->ch[1]->dis + 1 : 0;
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
        now->sumValue = getSumValue(now->ch[0]) + getSumValue(now->ch[1]) + now->value;
    }

    void merge(LeftTree &otherTree) {
        root = merge(root,otherTree.root);
    }

    void deleteMax() {
        if(root == NULL) return;
        root = merge(root->ch[0],root->ch[1]);
    }

    Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->value < b->value) {
            swap(a,b);
        }
        a->ch[1] = merge(a->ch[1],b);
        if(a->ch[0] == NULL || a->ch[0]->dis < a->ch[1]->dis) {
            swap(a->ch[0],a->ch[1]);
        }
        updateInfo(a);
        return a;
    }


};

long long M,result = 0;

void dfs(int now,Graph &graph,LeftTree *trees,long long *values,long long *weight) {
    trees[now] = LeftTree(values[now]);
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        dfs(tmpEdge.to,graph,trees,values,weight);
        trees[now].merge(trees[tmpEdge.to]);
    }
    while(trees[now].getSumValue() > M) {
        trees[now].deleteMax();
    }
    result = max(result,weight[now] * trees[now].getSize());
}

int main() {
    int N = read<int>();
    M = read<int>();
    Graph graph(N - 1,N);
    long long *values = new long long[N],*weight = new long long[N];
    for(int i = 0;i < N;i++) {
        int B = read<int>(),C = read<int>(),L = read<int>();
        B--;
        if(B != -1) {
            graph.addEdge(B,i);
        }
        values[i] = C;
        weight[i] = L;
    }
    LeftTree *trees = new LeftTree[N];
    dfs(0,graph,trees,values,weight);
    printf("%lld\n",result);
    return 0;
}
