#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),a = read<int>(),b = read<int>();
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
    }
    sort(values,values + n);
    for(int nowRound = 1;nowRound <= n;nowRound++) {
        long long result = 0;
        int k = 1;
        for(int nowPos = n - nowRound;nowPos < n;nowPos++) {
            printf("%d=%d ",nowPos,values[nowPos]);
            result += values[nowPos] * 1LL * (k * 1LL * k + a * k + b);
            k++;
        }
        printf("\n");
        printf("%lld\n",result);
    }
    return 0;
}

