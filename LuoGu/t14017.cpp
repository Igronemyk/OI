#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long quickPow(long long a,long long b,int p) {
    a %= p;
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * 1LL * base) % p;
        base = (base * 1LL * base) % p;
        b >>= 1;
    }
    return result;
}

long long quickPow(long long a,long long b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

int main() {
    int n = read<int>(),m = read<int>();
    long long *values = new long long[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<long long>();
    }
    for(int i = 0;i < m;i++) {
        int opt = read<int>(),l = read<int>(),r = read<int>();
        l--;r--;
        if(opt == 1) {
            int addValue = read<int>();
            for(int j = l;j <= r;j++) {
                values[j] += addValue;
            }
        }else {
            int p = read<int>();
            long long nowValue = 1;
            for(int j = r;j > l;j--) {
                nowValue = quickPow(values[j],nowValue);
            }
            printf("%lld\n",quickPow(values[l],nowValue,p));
        }
    }
    return 0;
}

