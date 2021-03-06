#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

int myPow(int a,int b){
    int result = 1,base = a;
    while(b){
        if(b & 1) result*=base;
        base*=base;
        b >>= 1;
    }
    return result;
}

int graph[10][10],visit[59049][10],dp[10][59049];



int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        memset(graph,INF,sizeof(graph));
        memset(visit,0,sizeof(visit));
        memset(dp,INF,sizeof(dp));
        for(int i = 0;i < m;i++){
            int from,to,weight;
            scanf("%d%d%d",&from,&to,&weight);
            from--;to--;
            graph[from][to] = min(graph[from][to],weight);
            graph[to][from] = min(graph[to][from],weight);
        }
        int maxState = myPow(3,n);
        for(int i = 0;i < maxState;i++){
            int tmpState = i,index = 0;
            while(tmpState){
                visit[i][index++] = tmpState % 3;
                tmpState /= 3;
            }
        }
        for(int i = 0;i < n;i++) dp[i][myPow(3,i)] = 0;
        int ans = INF;
        for(int i = 0;i < maxState;i++){
            bool canUpdate = true;
            for(int j = 0;j < n;j++){
                if(!visit[i][j]) canUpdate = false;
                if(dp[j][i] == INF) continue;
                for(int k = 0;k < n;k++){
                    if(k == j || graph[j][k] == INF || visit[i][k] == 2) continue;
                    dp[k][i + myPow(3,k)] = min(dp[k][i + myPow(3,k)],dp[j][i] + graph[j][k]);
                }
            }
            if(canUpdate){
                for(int j = 0;j < n;j++){
                    ans = min(ans,dp[j][i]);
                }
            }
        }
        printf("%d\n",ans == INF ? -1 : ans);
    }
    return 0;
}
