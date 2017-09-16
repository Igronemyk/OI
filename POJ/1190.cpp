#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f;

int N,M,*minVolume,*minArea;

int ans = INF;

void dfs(int nowLevel,int nowRadius,int nowHeight,int nowArea,int leftVolume){
    printf("%d %d %d %d %d\n",nowLevel,nowRadius,nowHeight,nowArea,leftVolume);
    if(nowLevel == 0){
        if(leftVolume == 0) ans = min(ans,nowArea);
        return;
    }
    if(leftVolume < minVolume[nowLevel]) return;
    if(ans - nowArea < minArea[nowLevel]) return;
    if(nowArea + 2 * leftVolume / nowRadius > ans) return;
    for(int i = nowRadius;i >= nowLevel;i--){
        if(nowLevel == M) nowArea = i * i;
        int maxHeight = min(nowHeight,(leftVolume - minVolume[nowLevel - 1]) / i / i);
        for(int j = maxHeight;j >= nowLevel;j--){
            dfs(nowLevel - 1,i - 1,j - 1,nowArea + 2 * i * j,leftVolume - i * i * j);
        }
    }
}

int main(){
    minVolume = new int[21];
    minArea = new int[21];
    minVolume[0] = 0;
    minArea[0] = 0;
    for(int i = 1;i <= 20;i++){
        minVolume[i] = minVolume[i - 1] + i * i * i;
        minArea[i] = minArea[i - 1] + 2 * i * i;
    }
    while(~scanf("%d%d",&N,&M)){
        ans = INF;
        dfs(M,(int)sqrt(N),N,0,N);
        printf("%d\n",ans == INF ? 0 : ans);
    }
    return 0;
}
