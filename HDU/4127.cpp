#include <cstdio>
#include <algorithm>

using namespace std;

int N,graph[8][8],visit[8][8];

inline int read(){
    int result = 0,f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

e

int main(){
    while(~scanf("%d",&N)){
        if(N == 0) break;
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                graph[i][j] = read();
            }
        }


    }
    return 0;
}


