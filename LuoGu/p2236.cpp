#include <cstdio>
#define EPS 1e-10

double pre[100];
int N,M,X,Y;
double ans;
int result = 0;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

void dfs(int nowPos,int nowSelect,double nowValue){
    if(M - nowPos < N - nowSelect) return;
    if(ans - (pre[nowPos + N - nowSelect] - pre[nowPos] + nowValue) > EPS) return;
    if(pre[M] - pre[M - N + nowSelect] + nowValue - ans > EPS) return;
    if(nowSelect == N){
        result++;
        return;
    }
    dfs(nowPos + 1,nowSelect,nowValue);
    dfs(nowPos + 1,nowSelect + 1,nowValue + 1.00 / (nowPos + 1));
}

int main(){
    N = read<int>();M = read<int>();X = read<int>();Y = read<int>();
    ans = (double)X / (double)Y;
    for(int i = 1;i <= M;i++) pre[i] = pre[i - 1] + 1.00 / i;
    dfs(0,0,0);
    printf("%d\n",result);
    return 0;
}
