#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int MAX_VAL_RANGE = 3000000;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isPrime[MAX_VAL_RANGE + 1];
int primes[MAX_VAL_RANGE + 1],primeCount;
long long phi[MAX_VAL_RANGE + 1],mu[MAX_VAL_RANGE + 1];
map<int,long long> phiAns,muAns;

void getPrimeAndMuAndPhi() {
    memset(isPrime,true,sizeof(bool) * MAX_VAL_RANGE);
    isPrime[1] = false;
    phi[1] = 1;
    mu[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCount++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for(int j = 0;j < primeCount && i * primes[j] <= MAX_VAL_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] != 0) {
                phi[i * primes[j]] = phi[i]  * phi[primes[j]];
                mu[i * primes[j]] = -mu[i];
            }else {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
        }
    }
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        phi[i] += phi[i - 1];
        mu[i] += mu[i - 1];
    }
}

long long getMu(long long n) {
    if(n <= MAX_VAL_RANGE) return mu[n];
    if(muAns.count(n) != 0) return muAns[n];
    long long ans = 1;
    for(long long i = 2;i <= n;i++) {
        long long jump = n / (n / i);
        ans -= (jump - i + 1) * getMu(n / i);
        i = jump;
    }
    muAns[n] = ans;
    return ans;
}

long long getPhi(long long n) {
    if(n <= MAX_VAL_RANGE) return phi[n];
    if(phiAns.count(n) != 0) return phiAns[n];
    long long ans = n * (n + 1) / 2;
    for(long long i = 2;i <= n;i++) {
        long long jump = n / (n / i);
        ans -= (jump - i + 1) * getPhi(n / i);
        i = jump;
    }
    phiAns[n] = ans;
    return ans;
}

int main() {
    getPrimeAndMuAndPhi();
    int T = read<int>();
    while(T--) {
        long long N = read<int>();
        printf("%lld %lld\n",getPhi(N),getMu(N));
    }
    return 0;
}
