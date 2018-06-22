#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 1e7;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int p;
int primes[MAX_VAL_RANGE + 1],phi[MAX_VAL_RANGE + 1],primeCnt;
bool isPrime[MAX_VAL_RANGE +1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    for(int i = 2;i <= MAX_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0;j < primeCnt && i * primes[j] <= MAX_VAL_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }else {
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            }
        }
    }
}

int quickPow(long long a,long long b,int p) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return static_cast<int>(result % p);
}

int getRes(int value) {
    if(value == 1) return 0;
    return quickPow(2,getRes(phi[value]) + phi[value],value);
}

int main() {
    getPrime();
    int T = read<int>();
    while(T--) {
        p = read<int>();
        printf("%d\n",static_cast<int>(getRes(p)));
    }
    return 0;
}
