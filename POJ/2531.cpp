#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int result = INF;

void solve(int &n,int doingN,int *A,int *B,int **graph,int nowA,int nowB,int ans){
    if(ans > result) return;
    if(doingN == n){

        result = min(result,ans);
        return;
    }
    int sumA = 0,sumB = 0;
    for(int i = 0;i < nowA;i++){
        sumA += graph[A[i]][doingN];
    }
    for(int i = 0;i < nowB;i++){
        sumB += graph[B[i]][doingN];
    }
    A[nowA] = doingN;
    solve(n,doingN + 1,A,B,graph,nowA + 1,nowB,ans + sumA);
    B[nowB] = doingN;
    solve(n,doingN + 1,A,B,graph,nowA,nowB + 1,ans + sumB);
}

int main(){
    int n;
    while(~scanf("%d",&n)){
        int sum = 0,**graph = new int*[n];
        for(int i = 0;i < n;i++){
            graph[i] = new int[n];
            for(int j = 0;j < n;j++){
                graph[i][j] = read();
                sum += graph[i][j];
            }
        }
        int *A = new int[n],*B = new int[n];
        solve(n,0,A,B,graph,0,0,0);
        printf("%d\n",sum/2 - result);
    }
    return 0;
}
