#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;

int read(){
    int result = 0,f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

//dp[i][0] 自身是服务器
//dp[i][1] 自身不是服务器，孩子是服务器
//dp[i][2] 自身不是服务器，父亲是服务器

struct Node{
    int id;
    vector<Node *> links;
    Node(int id) : id(id) {}
    void addLink(Node *link){
        links.push_back(link);
    }
};

void dp(Node *now,int fatherId,int **f){
    for(vector<Node *>::iterator it = now->links.begin();it != now->links.end();it++){
        Node *link = *it;
        if(link->id == fatherId) continue;
        dp(link,now->id,f);
        f[now->id][0] += min(f[link->id][0],f[link->id][2]);
        f[now->id][2] += f[link->id][1];
    }
    for(vector<Node *>::iterator it = now->links.begin();it != now->links.end();it++){
        Node *link = *it;
        if(link->id == fatherId) continue;
        f[now->id][1] = min(f[now->id][1],f[now->id][2] + f[link->id][0] - f[link->id][1]);
    }
}

int main(){
    while(true){
        N = read();
        Node **nodes = new Node*[N];
        for(int i = 0;i < N;i++) nodes[i] = new Node(i);
        for(int i = 0;i < N - 1;i++){
            int nodeA = read(),nodeB = read();
            nodeA--;nodeB--;
            nodes[nodeA]->addLink(nodes[nodeB]);
            nodes[nodeB]->addLink(nodes[nodeA]);
        }
        int **f = new int*[N];
        for(int i = 0;i < N;i++){
            f[i] = new int[3];
            f[i][0] = 1;
            f[i][1] = N + 1;
            f[i][2] = 0;
        }
        dp(nodes[0],-1,f);
        printf("%d\n",min(f[0][0],f[0][1]));
        int status = read();
        if(status == -1) break;
    }
    return 0;
}
