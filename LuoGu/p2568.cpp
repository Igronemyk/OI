#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e7;

int primes[MAX_VAL_RANGE + 1],phi[MAX_VAL_RANGE + 1],primeCount = 0;
long long f[MAX_VAL_RANGE + 1];

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

void getPrimeAndPhi() {
    phi[1] = 1;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        if(phi[i] == 0) {
            primes[primeCount++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0;j < primeCount && i * primes[j] <= MAX_VAL_RANGE;j++) {
            if(i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }else {
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            }
        }
        f[i] = f[i - 1] + (phi[i] << 1);
    }
}

int main() {
    getPrimeAndPhi();
    int n = read<int>();
    long long result = 0;
    for(int i = 0;i < primeCount && primes[i] <= n;i++) {
        result += 1 + f[n / primes[i]];
    }
    printf("%lld\n",result);
    return 0;
}

