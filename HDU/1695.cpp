#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e5;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isPrime[MAX_VAL_RANGE + 1];
int primes[MAX_VAL_RANGE + 1],mu[MAX_VAL_RANGE + 1],primeCount = 0;

void getPrimeAndMu() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
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
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        printf("Case %d: ",nowCase);
        int a = read<int>(),b = read<int>(),c = read<int>(),d = read<int>(),k = read<int>();
        if(k == 0) {
            printf("0\n");
            continue;
        }
        b /= k; d /= k;
        if(b > d) {
            swap(b,d);
        }
        long long result = 0,errCount = 0;
        for(int i = 1;i <= b;i++) {
            result += mu[i] * (b / i) * 1LL * (d / i);
            errCount += mu[i] * (b / i) * 1LL * (b / i);
        }
        printf("%lld\n",result - (errCount >> 1LL));
    }
    return 0;
}
