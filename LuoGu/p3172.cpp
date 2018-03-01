#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e5;
const int MODDER = 1e9 + 7;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0'){if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int quickPow(int a,int b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % MODDER;
        base = (base * base) % MODDER;
        b >>= 1;
    }
    return result;
}

bool isPrime[MAX_VAL_RANGE + 1];
int primes[MAX_VAL_RANGE + 1],mu[MAX_VAL_RANGE + 1],primeCount = 0;

void getPrimeAndMu() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    for(int i = 1;i <= MAX_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCount++] = i;
            mu[i] = -1;
        }
        for(int j = 0;j < primeCount && i * primes[j] <= MAX_VAL_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] != 0) {
                mu[i * primes[j]] = -mu[i];
            }else {
                break;
            }
        }
    }
}

int main() {
    getPrimeAndMu();
    int N = read<int>(),K = read<int>(),L = read<int>(),H = read<int>();
    H /= K; L = (L - 1) / K;
    int result = 0;
    for(int i = 1;i <= H - L;i++) {
        int cnt = H / i - L / i;
        result += mu[i] * (((quickPow(cnt,N) - cnt) % MODDER + MODDER) % MODDER);
        result = (result % MODDER + MODDER) % MODDER;
    }
    if(L == 1) result = (result + 1) % MODDER;
    printf("%d\n",result);
    return 0;
}
