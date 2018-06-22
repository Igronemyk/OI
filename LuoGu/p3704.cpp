#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1e6;
const int MODDER = 1e9 + 7;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int quickPow(int a,long long b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % MODDER;
        base = (base * base) % MODDER;
        b >>= 1;
    }
    return static_cast<int>(result);
}

int inv(int value) {
    return quickPow(value,MODDER - 2);
}

int primes[MAXN + 1],mu[MAXN + 1],f[MAXN + 1],val[MAXN + 1],primeCnt;
bool isPrime[MAXN + 1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    f[1] = 1;
    for(int i = 2;i <= MAXN;i++) {
        f[i] = (f[i - 1] + f[i - 2]) % MODDER;
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            mu[i] = -1;
        }
        for(int j = 0;j < primeCnt && i * primes[j] <= MAXN;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] == 0) {
                break;
            }else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
}

void init() {
    for(int i = 1;i <= MAXN;i++) {
        val[i] = 1;
    }
    for(int i = 1;i <= MAXN;i++) {
        int invValue = inv(f[i]);
        for(int j = i;j <= MAXN;j += i) {
            if(mu[j / i] == 1) {
                val[j] = (val[j] * 1LL * f[i]) % MODDER;
            }else if(mu[j / i] == -1) {
                val[j] = (val[j] * 1LL * invValue) % MODDER;
            }
        }
    }
    val[0] = 1;
    for(int i = 1;i <= MAXN;i++) {
        val[i] = (val[i] * 1LL * val[i - 1]) % MODDER;
    }
}

int main() {
    getPrime();
    init();
    int T = read<int>();
    while(T--) {
        int n = read<int>(),m = read<int>(),limit = min(n,m),result = 1;
        for(int i = 1;i <= limit;i++) {
            int jumpTo = min(n / (n / i),m / (m / i));
            result = (result * 1LL * quickPow((val[jumpTo] * 1LL * inv(val[i - 1])) % MODDER,(n / i) * 1LL * (m / i))) % MODDER;
            i = jumpTo;
        }
        printf("%d\n",result);
    }
    return 0;
}
