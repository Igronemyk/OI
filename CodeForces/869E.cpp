#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int graph[2510][2510];

int main(){
    int n = read<int>(),m = read<int>(),q = read<int>();
    for(int i = 0;i < q;i++){
        int t = read<int>();
        int r1 = read<int>(),c1 = read<int>(),r2 = read<int>(),c2 = read<int>();
        switch(t){
        case 1:{
            graph[r1][c1]++;
            graph[r2 + 1][c2 + 1]--;
            break;
        }
        case 2:{
            graph[r1][c1]--;
            graph[r2 + 1][c2 + 1]++;
            break;
        }
        case 3:{
            int countValue = 0;
            if(r1 > r2) {
                int tmp = r1;
                r1 = r2;
                r2 = tmp;
            }
            if(c1 > c2){
                int tmp = c1;
                c1 = c2;
                c2 = tmp;
            }

            for(int i = 0;i <= r2;i++){
                for(int j = 0;j <= c2;j++){
                    countValue += graph[i][j];
                }
            }
            for(int i = 0;i <= r1 - 1;i++){
                for(int j = 0;j <= c2;j++){
                    countValue -= graph[i][j];
                }
            }
            for(int i = 0;i <= r2;i++){
                for(int j = 0;j <= c2 - 1;j++){
                    countValue -= graph[i][j];
                }
            }
            for(int i = 0;i <= r1 - 1;i++){
                for(int j = 0;j <= r2 - 1;j++){
                    countValue += graph[i][j];
                }
            }
            if(countValue == 0){
                printf("YES\n");
            }else{
                printf("NO\n");
            }
            break;
        }
        }
    }
    return 0;
}

