#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    long long P = read<int>(),B = read<int>(),N = read<int>();
    map<long long,int> val;
    int sqrtValue = static_cast<int>(ceil(sqrt(P)));
    long long nowValue = N;
    for(int i = 0;i <= sqrtValue;i++) {
        val[nowValue] = i;
        nowValue = (nowValue * B) % P;
    }
    long long stepValue = 1;
    for(int i = 1;i <= sqrtValue;i++) {
        stepValue = (stepValue * B) % P;
    }
    nowValue = stepValue;
    for(int i = 1;i <= sqrtValue;i++) {
        if(val.count(nowValue) != 0) {
            printf("%d\n",i * sqrtValue - val[nowValue]);
            return 0;
        }
        nowValue = (nowValue * stepValue) % P;
    }
    printf("no solution\n");
    return 0;
}
