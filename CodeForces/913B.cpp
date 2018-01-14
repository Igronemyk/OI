#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>

using namespace std;

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

void dfs(int now,int father,Graph &graph,bool *isLeafNode,bool *isRightNode) {
    int countLeftNodeChild = 0;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        if(tmpEdge.to == father) continue;
        isLeafNode[now] = false;
        dfs(tmpEdge.to,now,graph,isLeafNode,isRightNode);
        if(isLeafNode[tmpEdge.to]) {
            countLeftNodeChild++;
        }
    }
    if(countLeftNodeChild >= 3) {
        isRightNode[now] = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    Graph graph((n - 1) * 2,n);
    for(int i = 1;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        tmpValue--;
        graph.addEdge(i,tmpValue);
        graph.addEdge(tmpValue,i);
    }
    bool *isLeafNode = new bool[n],*isRightNode = new bool[n];
    memset(isLeafNode,true,sizeof(bool) * n);
    memset(isRightNode,false,sizeof(bool) * n);
    dfs(0,-1,graph,isLeafNode,isRightNode);
    bool flag = true;
    for(int i = 0;i < n;i++) {
        if(!isLeafNode[i] && !isRightNode[i]) {
            flag = false;
            break;
        }
    }
    cout << (flag ? "Yes" : "No") << endl;
    return 0;
}

