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

bool visit[16];
int countTimes[16];

int main(){
    int n = read<int>(),m = read<int>();
    int stateCount = (1 << m);
    for(int i = 0;i < n;i++){
        int tmpValue = 0;
        for(int j = 0;j < m;j++){
            tmpValue += (read<int>() == 0) ? 0 : (1 << j);
        }
        visit[tmpValue] = true;
        countTimes[tmpValue]++;
    }
    bool solve = false;
    for(int i = 0;i < stateCount;i++){
        if(!visit[i]) continue;
        for(int j = 0;j < stateCount;j++){
            if(!visit[j]) continue;
            if(i == j && countTimes[i] == 1) continue;
            if((i & j) == 0){
                solve = true;
                goto outside;
            }
        }
    }
    outside:
    if(!solve && n == 1 && visit[0]) solve = true;
    printf(solve ? "YES\n" : "NO\n");
    return 0;
}
