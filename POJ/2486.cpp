#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,K;

struct Node{
    int id;
    vector<Node *> links;
    Node(int id) : id(id) { }
    void addLink(Node *link){
        links.push_back(link);
    }
};

void dp(Node *now,int fatherId,int ***f){
    for(vector<Node *>::iterator it = now->links.begin();it != now->links.end();it++){
        Node *link = *it;
        if(link->id == fatherId) continue;
        dp(link,now->id,f);
        for(int i = K;i >= 1;i--){
            for(int j = 0;j < i;j++){
                if(i - j - 2 >= 0){
                    f[now->id][i][1] = max(f[now->id][i][1],f[now->id][j][1] + f[link->id][i - j - 2][1]);
                    f[now->id][i][0] = max(f[now->id][i][0],f[now->id][j][0] + f[link->id][i - j - 2][1]);
                }
                f[now->id][i][0] = max(f[now->id][i][0],f[now->id][j][1] + f[link->id][i - j - 1][0]);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    while(cin >> N >> K){
        Node **nodes = new Node*[N];
        for(int i = 0;i < N;i++) nodes[i] = new Node(i);
        int *weight = new int[N];
        for(int i = 0;i < N;i++){
            cin >> weight[i];
        }
        for(int i = 0;i < N - 1;i++){
            int nodeA,nodeB;
            cin >> nodeA >> nodeB;
            nodeA--;nodeB--;
            nodes[nodeA]->addLink(nodes[nodeB]);
            nodes[nodeB]->addLink(nodes[nodeA]);
        }
        int ***f = new int**[N];//1返回0不返回
        for(int i = 0;i < N;i++){
            f[i] = new int*[K + 1];
            for(int j = 0;j < K + 1;j++){
                f[i][j] = new int[2];
                fill(f[i][j],f[i][j] + 2,weight[i]);
            }
        }
        dp(nodes[0],-1,f);
        cout << max(f[0][K][0],f[0][K][1]) << endl;
    }
    return 0;
}
