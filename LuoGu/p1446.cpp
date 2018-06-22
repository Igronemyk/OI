#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 60;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int fac[MAX_VAL_RANGE + 1],facInv[MAX_VAL_RANGE + 1],p;

int quickPow(int a,int b) {
    int result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return result % p;
}

int inv(int value) {
    return quickPow(value,p - 2);
}

void init(int n) {
    fac[0] = 1;
    facInv[0] = 1;
    for(int i = 1;i <= n;i++) {
        fac[i] = fac[i - 1] * i % p;
    }
    facInv[n] = inv(fac[n]);
    for(int i = n - 1;i >= 1;i--) {
        facInv[i] = facInv[i + 1] * (i + 1) % p;
    }
}

int main() {
    int a = read<int>(),b = read<int>(),c = read<int>(),m = read<int>();
    p = read<int>();
    init(max(a + b + c,m + 1));
    printf("%d\n",fac[a + b + c] % p * facInv[a] * facInv[b] * facInv[c] % p * inv(m + 1) % p);
    return 0;
}
