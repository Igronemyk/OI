#include <cstdio>

inline int readInt(){
    int result = 0, f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(f == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

inline long long readLong(){
    long long result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(f == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long mp[20][10];

int main(){
    int T = readInt();
    for(int i = 2;i < 20;i++){
        for(int j = 0;j < 10;j++){
            for(int k = 0;k < 10;k++){
                mp[i][j] += mp[i - 1][k];
                if(j == 4 && k == 9) mp[i][j]++;
            }
        }
    }/*
    while(T--){
        long long N = readLong();
        int len = 0;long long tmp = N;
        while(tmp){

        }
    }*/
    printf("%lld\n",mp[3][4]);
    return 0;
}

//i = 20
