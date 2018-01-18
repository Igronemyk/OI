#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_RANGE = 1e6 + 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= - 1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isPrime[MAX_RANGE + 1];
int primes[MAX_RANGE + 1],primeCount;
long long sum[MAX_RANGE + 1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[0] = false;
    isPrime[1] = false;
    sum[1] = 1;
    for(int i = 2;i <= MAX_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCount++] = i;
            sum[i] = i + 1;
        }
        for(int j = 0;j < primeCount && i * primes[j] <= MAX_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            int tmp = i;
            while(tmp % primes[j] == 0) tmp /= primes[j];
            sum[i * primes[j]] = sum[i] * primes[j] + sum[tmp];
            if(i % primes[j] == 0) break;
        }
    }
}

int main() {
    getPrime();
    int n = read<int>();
    long long result = 0;
    for(int i = 1;i <= n;i++) {
        result = result + n - sum[i];
        printf("%lld ",result);
    }
    printf("\n");
    return 0;
}
