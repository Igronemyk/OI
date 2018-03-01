#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9'|| c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result* f;
}

long long quickPow(int a,int b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

int getMu(int value) {
    if(value == 1) return 1;
    int cnt = 0;
    for(int i = 2;i * i <= value;i++) {
        if(value % i == 0) {
            cnt++;
            value /= i;
        }
        if(value % i == 0) {
            return 0;
        }
    }
    if(value > 1) cnt++;
    if(cnt & 1) {
        return -1;
    }else {
        return 1;
    }
}

int main() {
    int N = read<int>(),M = read<int>();
    long long result = 0;
    for(int i = 1;i * i <= M;i++) {
        if(M % i != 0) continue;
        result += getMu(i) * quickPow(M / i,N);
        if(i * i != M) {
            result += getMu(M / i) * quickPow(i,N);
        }
    }
    printf("%lld\n",result);
    return 0;
}
