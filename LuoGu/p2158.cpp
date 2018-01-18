#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_RANGE = 40001;

bool isPrime[MAX_RANGE];
int primes[MAX_RANGE],phi[MAX_RANGE];

void getPrimeAndPhi() {
    memset(isPrime,true,sizeof(bool) * MAX_RANGE);
    isPrime[0] = 0;
    isPrime[1] = 0;
    int primeCount = 0;
    for(int i = 2;i <= MAX_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCount++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0;j < primeCount && i * primes[j] <= MAX_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
            }else {
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            }
            if(i % primes[j] == 0) break;
        }
    }

}

int main() {
    getPrimeAndPhi();
    int n;
    scanf("%d",&n);
    if(n == 1) {
        printf("1\n");
    }else if(n == 2) {
        printf("3\n");
    }else {
        long long result = 0;
        for(int i = 3;i <= n;i++) {
            result += phi[i - 1];
        }
        result *= 2;
        result += 3;
        printf("%lld\n",result);
    }
    return 0;
}
