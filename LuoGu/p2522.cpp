#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_VAL_RANGE = 5e4;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool isPrime[MAX_VAL_RANGE + 1];
int primes[MAX_VAL_RANGE + 1],mu[MAX_VAL_RANGE + 1],sumMu[MAX_VAL_RANGE + 1],primeCount = 0;

void getPrimeAndMu() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    sumMu[1] = 1;
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
        sumMu[i] = sumMu[i - 1] + mu[i];
    }
}

long long getRes(int a,int b,int d) {
    a /= d;b /= d;
    int minValue = min(a,b);
    long long result = 0;
    for(int i = 1;i <= minValue;i++) {
        int jumpValue = min(a / (a / i),b / (b / i));
        result += (sumMu[jumpValue] - sumMu[i - 1]) * (a / i) * 1LL * (b / i);
        i = jumpValue;
    }
    return result;
}

int main() {
    getPrimeAndMu();
    int n = read<int>();
    while(n--) {
        long long result = 0;
        int a = read<int>(),b = read<int>(),c = read<int>(),d = read<int>(),k = read<int>();
        result += getRes(b,d,k);
        result -= getRes(a - 1,d,k);
        result -= getRes(b,c - 1,k);
        result += getRes(a - 1,c - 1,k);
        printf("%lld\n",result);
    }
    return 0;
}


