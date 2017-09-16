#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

int n;

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while( c >'9' ||c <'0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool dfs(int nowCollect,int &maxCollect,int nowLocation,int nowLen,int &maxLen,int *value,bool *visit){
    if(nowCollect == maxCollect) return true;
    for(int i = nowLocation;i < n;i++){
        if(visit[i]) continue;
        if(nowLen + value[i] == maxLen){
            visit[i] = true;
            if(dfs(nowCollect + 1,maxCollect,0,0,maxLen,value,visit)) return true;
            visit[i] = false;
            return false;
        }else if(nowLen + value[i] < maxLen){
            visit[i] = true;
            if(dfs(nowCollect,maxCollect,i + 1,nowLen + value[i],maxLen,value,visit)) return true;
            visit[i] = false;
            if(nowLen == 0) return false;
            while(i < n && value[i] == value[i + 1]) i++;
        }
    }
    return false;
}

int main(){
    while(~scanf("%d",&n)){
        if(n == 0) break;
        int *value = new int[n];
        int sum = 0;
        for(int i = 0;i < n;i++){
            value[i] = read();
            sum += value[i];
        }
        sort(value,value + n,greater<int>());
        bool *visit = new bool[n];
        fill(visit,visit +n,false);
        for(int i = value[0];i <= sum;i++){
            if(sum % i != 0) continue;
            int total = sum / i;
            if(dfs(0,total,0,0,i,value,visit)) {
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
