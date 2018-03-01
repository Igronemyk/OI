#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstddef>

using namespace std;

const int MAX_VAL_RANGE = 10010;

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
                mu[i * primes[j]] = mu[i] * -1;
            }else {
                break;
            }
        }
    }
}

long long calc(int value) {
    return value * 1LL * (value - 1) * (value - 2) * (value - 3) / 24;
}

int cnt[MAX_VAL_RANGE + 1];

int main() {
    getPrimeAndMu();
    int N;
    while(~scanf("%d",&N)) {
        memset(cnt,0,sizeof(cnt));
        for(int i = 0;i < N;i++) {
            int tmpValue = read<int>(),top = static_cast<int>(sqrt(tmpValue));
            for(int j = 1;j <= top;j++) {
                if(tmpValue % j != 0) continue;
                cnt[j]++;
                if(j * j != tmpValue) {
                    cnt[tmpValue / j]++;
                }
            }
        }
        long long result = 0;
        for(int i = 1;i <= MAX_VAL_RANGE;i++) {
            result += mu[i] * calc(cnt[i]);
        }
        printf("%lld\n",result);
    }
    return 0;
}
