#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main(){
    int n;
    while(~scanf("%d",&n)){
        int *nums = new int[n];
        for(int i = 0;i < n;i++){
            scanf("%d",&nums[i]);
        }
        int **dp = new int*[N];
        for(int i = 0;i < N;i++){
            dp[i] = new int[N];
            fill(dp[i],dp[i] + N,INF);
        }
        for(int i = 0;i < N;i++){
            dp[i][i] = 1;
        }
        for(int len =2;len <= n;len++){

        }
    }
    return 0;
}
