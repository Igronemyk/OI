#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

const long long MODDER = 999911659;
const long long PHI_MODDER = MODDER - 1;
const int VALUES_COUNT = 4;
const long long VALUES[4] = {2,3,4679,35617};
const int MAX_VAL_RANGE = 35617;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long fac[MAX_VAL_RANGE + 1];

long long quickPow(long long a,long long b,long long p) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return result;
}

long long inv(long long val,long long p) {
    return quickPow(val % p,p - 2,p);
}

long long comb(long long n,long long m,long long p) {
    if(m > n) return 0;
    return (fac[n] * 1LL * inv((fac[m] * 1LL * fac[n - m]) % p,p)) % p;
}

long long lucas(long long n,long long m,long long p) {
    if(m == 0) {
        return 1;
    }
    return (lucas(n / p,m / p,p) * 1LL * comb(n % p,m % p,p)) % p;
}

long long solve(long long N,long long p) {
    fac[0] = 1;
    for(int i = 1;i <= MAX_VAL_RANGE;i++) {
        fac[i] = fac[i - 1] * i % p;
    }
    long long result = 0;
    for(int i = 1;i * i <= N;i++) {
        if(N % i != 0) continue;
        result = (result + lucas(N,i,p)) % p;
        if(i * i != N) {
            int j = N / i;
            result = (result + lucas(N,j,p)) % p;
        }
    }
    return result;
}

long long CRT(long long *values,const long long *modders) {
    long long result = 0;
    for(int i = 0;i < VALUES_COUNT;i++) {
        result += inv(PHI_MODDER / modders[i],modders[i]) * (PHI_MODDER / modders[i]) % PHI_MODDER * values[i] % PHI_MODDER;
        result %= PHI_MODDER;
    }
    return result;
}

int main() {
    long long N = read<int>(),G = read<int>();
    if(G % MODDER == 0) {
        printf("%d\n",0);
        return 0;
    }
    long long *values = new long long[VALUES_COUNT];
    for(int i = 0;i < VALUES_COUNT;i++) {
        values[i] = solve(N,VALUES[i]);
    }
    printf("%lld\n",quickPow(G,CRT(values,VALUES),MODDER));
    return 0;
}
