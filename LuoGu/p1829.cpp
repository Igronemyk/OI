#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int MAX_VAL_RANGE = 1e7;
const int PRIME_ALL_CNT = 664579;
const int MODDER = 20101009;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int primes[PRIME_ALL_CNT + 1],f[MAX_VAL_RANGE + 1],sumVal[MAX_VAL_RANGE + 1],primeCnt;
bool isPrime[MAX_VAL_RANGE + 1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    f[1] = 1;
    sumVal[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            f[i] = (1 - i + MODDER) % MODDER;
        }
        for(int j = 0;j < primeCnt && primes[j] * 1LL * i <= MAX_VAL_RANGE;j++) {
            isPrime[primes[j] * i] = false;
            if(i % primes[j] == 0) {
                f[i * primes[j]] = f[i];
                break;
            }else {
                f[i * primes[j]] = (f[i] * 1LL * ((1 - primes[j] + MODDER) % MODDER)) % MODDER;
            }
        }
        f[i] = (f[i - 1] + f[i] * 1LL * i % MODDER) % MODDER;
        sumVal[i] = (sumVal[i - 1] + i) % MODDER;
    }
}

int main() {
    getPrime();
    int n = read<int>(),m = read<int>(),minValue = min(n,m);
    long long result = 0;
    for(int i = 1;i <= minValue;i++) {
        int jumpTo = min(n / (n / i),m / (m / i));
        result = (result + (sumVal[n / i] * 1LL * sumVal[m / i] % MODDER * ((f[jumpTo] - f[i - 1] + MODDER) % MODDER)) % MODDER) % MODDER;
        i = jumpTo;
    }
    printf("%lld\n",result);
    return 0;
}
