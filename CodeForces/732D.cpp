#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 0x3f3f3f3f;
int n,m;
bool vis[100001];

bool check(int day,int *exam,int *pre){
    int passed = 0,useDay = 0;
    memset(vis,0,sizeof(vis));
    for(int i = day;i >= 1;i--){
        int passId = exam[i];
        if(passId == 0){
            useDay--;
        }else{
            if(vis[passId]){
                useDay--;
            }else{
                vis[passId] = true;
                useDay += pre[passId];
                passed++;
            }
        }
        if(useDay < 0) useDay = 0;
    }
    return (useDay == 0 && passed == m);
}

int main(){
    n = read(),m = read();
    int *exam = new int[n + 1],*pre = new int[m + 1];
    for(int i = 1;i <= n;i++) exam[i] = read();
    for(int i = 1;i <= m;i++) pre[i] = read();
    int left = 0,right = n;
    int result = INF;
    while(left <= right){
        int mid = (left + right) >> 1;
        if(check(mid,exam,pre)){
            right = mid - 1;
            result = min(result,mid);
        }else{
            left = mid + 1;
        }
    }
    printf("%d\n",result == INF ? -1 : result);
    return 0;
}
