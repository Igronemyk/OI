#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long sum,result;

int weight[100000];

vector<int> graph[100000];

long long myAbs(long long value){
    return value < 0 ? value * -1 : value;
}

long long dfs(int now,int fatherId){
    long long tot = weight[now];
    for(vector<int>::iterator it = graph[now].begin();it != graph[now].end();it++){
        if(*it == fatherId) continue;
        tot += dfs(*it,now);
    }
    if(result == -1 || result > myAbs(sum - tot *2)) result = myAbs(sum - tot * 2);
    return tot;
}

int main(){
    int N,M,index = 1;
    while(~scanf("%d %d",&N,&M)){
        sum = 0;
        result = -1;
        if(N == 0 && M == 0) break;
        for(int i = 0;i < N;i++){
            scanf("%d",&weight[i]);
            sum += weight[i];
            graph[i].clear();
        }
        for(int i = 0;i < M;i++){
            int nodeA,nodeB;
            scanf("%d %d",&nodeA,&nodeB);
            nodeA--;nodeB--;
            graph[nodeA].push_back(nodeB);
            graph[nodeB].push_back(nodeA);
        }
        dfs(0,-1);
        printf("Case %d: %lld\n",index++,result);
    }
    return 0;
}
