#include <cstdio>

const int MAX_VAL_RANGE = 2e4;
const int p = 9901;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int fac[MAX_VAL_RANGE + 1];

int quickPow(int a,int b,int p) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return result;
}

int inv(int val,int p) {
    return quickPow(val,p - 2,p);
}

int comb(int n,int m,int p) {
    if(m > n) return 0;
    return (fac[n] * 1LL * inv((fac[m] * 1LL * fac[n - m]) % p,p)) % p;
}

int lucas(int n,int m,int p) {
    if(m == 0) {
        return 1;
    }
    return (lucas(n / p,m / p,p) * 1LL * comb(n % p,m % p,p)) % p;
}

void initFac() {
    fac[0] = 1;
    fac[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        fac[i] = fac[i - 1] * 1LL * i % p;
    }
}

int main() {
    initFac();
    int m = read<int>(),n = read<int>();
    printf("%d\n",lucas(m,n,p));
    return 0;
}
