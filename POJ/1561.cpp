#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f;

int myMerge(int *value,int start1,int end1,int start2,int end2){
    int dis1 = end1 - start1;
    int dis2 = end2 - start2;
    if(dis1 == 0){
        return value[start1] * value[start2] * value[end2];
    }else if(dis2 == 0){
        return value[start1] * value[end1] * value[start2];
    }else{
        return min(value[start1] * value[end1] * value[start2] + value[start1] * value[start2] * value[end2],value[end1] * value[start2] * value[end2] + value[start1] * value[end1] * value[end2]);
    }
}
int main(){
    int N;
    while(~scanf("%d",&N)){
        int *values = new int[N];
        int **dp = new int*[N + 1];
        for(int i = 0;i <= N;i++){
            dp[i] = new int[N];
            fill(dp[i],dp[i] + N,(i == 1 || i == 2) ? 0 : INF);
        }
        for(int i = 0;i < N;i++){
            scanf("%d",&values[i]);
        }
        for(int len = 3;len <= N;len++){
            for(int i = 0;i <= N - len;i++){
                for(int j = i;j < N && j - i + 1 < len;j++){
                    dp[len][i] = min(dp[len][i],dp[j - i + 1][i] + dp[len - (j - i + 1)][j + 1] + myMerge(values,i,j,j + 1,i + len - 1));
                }
            }
        }
        printf("%d\n",dp[N][0]);
    }
    return 0;
}
