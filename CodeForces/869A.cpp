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
bool visit[2000001];

int main(){
    int n = read<int>();
    long long result = 0;
    int **value = new int*[2];
    for(int i = 0;i < 2;i++) value[i] = new int[n];
    for(int i = 0;i < 2;i++) for(int j = 0;j < n;j++) {value[i][j] = read<int>();visit[value[i][j]] = true;}
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            int tmpValue = value[0][i] ^ value[1][j];
            if(tmpValue > 2000000) continue;
            if(visit[tmpValue]) result++;
        }
    }
    printf(result % 2 == 0 ? "Karen" : "Koyomi");
    return 0;
}
