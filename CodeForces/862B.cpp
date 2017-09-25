#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c >'9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

vector<int> graph[100000];
bool visit[100000],groups[100000];
int sizeA = 0,sizeB = 0;

void dfs(int now,int group){
    visit[now] = true;
    if(group){
        sizeB++;
        groups[now] = true;
    }else{
        sizeA++;
        groups[now] = false;
    }
    for(vector<int>::iterator it = graph[now].begin();it != graph[now].end();it++){
        if(visit[*it]) continue;
        dfs(*it,!group);
    }
}

int main(){
    int n = read<int>();
    for(int i = 0;i < n - 1;i++){
        int nodeA = read<int>(),nodeB = read<int>();
        nodeA--; nodeB--;
        graph[nodeA].push_back(nodeB);
        graph[nodeB].push_back(nodeA);
    }
    dfs(0,0);
    long long result = 0;
    for(int i = 0;i < n;i++){
        result += (groups[i] ? sizeA : sizeB) - static_cast<int>(graph[i].size());
    }
    cout << result / 2 << endl;
    return 0;
}
