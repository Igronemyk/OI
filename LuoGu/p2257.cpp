#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e7;
const int PRIME_ALL_CNT = 664579;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int primes[PRIME_ALL_CNT + 1],mu[MAX_VAL_RANGE + 1],primeCnt;
long long sum[MAX_VAL_RANGE + 1];
bool isPrime[MAX_VAL_RANGE + 1];


void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            mu[i] = -1;
        }
        for(int j = 0;j < primeCnt && i * primes[j] <= MAX_VAL_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] == 0) {
                break;
            }else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
    for(int i = 0;i < primeCnt;i++) {
        for(int j = 1;j * primes[i] <= MAX_VAL_RANGE;j++) {
            sum[j * primes[i]] += mu[j];
        }
    }
    for(int i = 1;i <= MAX_VAL_RANGE;i++) {
        sum[i] += sum[i - 1];
    }
}

int main() {
    getPrime();
    int T = read<int>();
    while(T--) {
        int N = read<int>(),M = read<int>(),minValue = min(N,M);
        long long result = 0;
        for(int i = 1;i <= minValue;i++) {
            int jumpTo = min(N / (N / i),M / (M / i));
            result += 1LL * (N / i) * (M / i) * (sum[jumpTo] - sum[i - 1]);
            i = jumpTo;
        }
        printf("%lld\n",result);
    }
    return 0;
}
