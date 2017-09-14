#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
const int INF = 0x3f3f3f3f;

struct Node;

struct Edge{
    int weight;
    Node *to;
    Edge(int weight,Node *to) : weight(weight) , to(to) { }
};

struct Node{
    int id;
    vector<Edge> edges;
    void addEdge(Edge edge){
        edges.push_back(edge);
    }
    bool isLeafNode(){
        return edges.size() == 0;
    }
    Node(int id) : id(id) {}
};

int dp(Node *now,int **f){
    if(now->isLeafNode()) return 1;
    int sum = 0;
    for(vector<Edge>::iterator it = now->edges.begin();it != now->edges.end();it++){
        int leafNum = dp(it->to,f);
        sum += leafNum;
        for(int i = sum;i >= 1;i--){
            for(int j = 0;j <= leafNum && j <= i;j++){
                f[now->id][i] = max(f[now->id][i],f[now->id][i - j] + f[it->to->id][j] - it->weight);
            }
        }
    }
    return sum;
}

int main(){
    int N,M;
    while(~scanf("%d%d",&N,&M)){
        Node **nodes = new Node*[N];
        for(int i = 0;i < N;i++) nodes[i] = new Node(i);
        for(int i = 0;i < N - M;i++){
            int k;
            scanf("%d",&k);
            for(int j = 0;j < k;j++){
                int id,cost;
                scanf("%d%d",&id,&cost);
                id--;
                nodes[i]->addEdge(Edge(cost,nodes[id]));
            }
        }
        int **f = new int*[N];
        for(int i = 0;i < N;i++){
            f[i] = new int[N + 1];
            fill(f[i],f[i] + N + 1,INF * -1);
            if(i >= N - M){
                scanf("%d",&f[i][1]);
            }
            f[i][0] = 0;
        }
        dp(nodes[0],f);
        for(int i = M;i >= 0;i--){
            if(f[0][i] >= 0){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
