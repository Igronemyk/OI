#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c- '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>(),T = read<int>();
    long long result = 0,nowHappy = 0;
    for(int i = 0;i < N;i++) {
        long long tmpValue = read<int>();
        if(tmpValue <= nowHappy) result -= nowHappy - tmpValue + 1;
        result += T;
        nowHappy = tmpValue + T - 1;
    }
    printf("%lld\n",result);
    return 0;
}
