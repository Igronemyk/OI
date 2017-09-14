#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node{
    int id;
    vector<Node *> childs;
    Node(int id) : id(id) {}

    void addChild(Node *child){
        childs.push_back(child);
    }

    int getChildsSize(){
        return static_cast<int>(childs.size());
    }
};

int dp(Node *now,int **f){
    int sum = 1;
    f[now->id][1] = now->getChildsSize();
    for(vector<Node *>::iterator it = now->childs.begin();it != now->childs.end();it++){
        Node *child = *it;
        int childSize = dp(child,f);
        sum += childSize;
        for(int i = sum;i >= 2;i--){
            for(int j = 1;j <= childSize && j <= i - 1;j++){
                f[now->id][i] = min(f[now->id][i],f[child->id][j] + f[now->id][i - j] - 1);
            }
        }
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    int N, P;
    while(cin >> N >> P){
        Node **nodes = new Node*[N];
        for(int i = 0;i < N;i++){
            nodes[i] = new Node(i);
        }
        for(int i = 0;i < N - 1;i++){
            int parent,child;
            cin >> parent >> child;
            parent--;child--;
            nodes[parent]->addChild(nodes[child]);
        }
        int **f = new int*[N + 1];
        for(int i = 0;i <= N;i++){
            f[i] = new int[N + 1];
            fill(f[i],f[i] + N + 1,0x3f3f3f3f);
        }
        dp(nodes[0],f);
        int ans = f[0][P];
        for(int i = 1;i < N;i++){
            ans = min(ans,f[i][P] + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
