#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N,resultId,resultValue;

int read(){
    int result = 0,f = 1;
    char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Node{
    int id;
    vector<Node *> links;
    void addLink(Node *link){
        links.push_back(link);
    }
    Node(int id) : id(id) {}
};

int dfs(Node *now,int fatherId){
    int sum = 1;
    int value = 0;
    for(vector<Node *>::iterator it = now->links.begin();it != now->links.end();it++){
        Node *link = *it;
        if(link->id == fatherId) continue;
        int subValue = dfs(link,now->id);
        value = max(value,subValue);
        sum += subValue;
    }
    value = max(value,N - sum);
    if(resultId == -1 || resultValue > value || (resultValue == value && resultId > now->id)){
        resultId = now->id;
        resultValue = value;
    }
    return sum;
}

int main(){
    int T = read();
    while(T--){
        N = read();
        resultId = -1;
        resultValue = -1;
        Node **nodes = new Node*[N];
        for(int i = 0;i < N;i++) nodes[i] = new Node(i);
        for(int i = 0;i < N - 1;i++){
            int nodeA = read(),nodeB = read();
            nodeA--;nodeB--;
            nodes[nodeA]->addLink(nodes[nodeB]);
            nodes[nodeB]->addLink(nodes[nodeA]);
        }
        dfs(nodes[0],-1);
        printf("%d %d\n",resultId + 1,resultValue);
    }
    return 0;
}
