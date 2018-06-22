#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const long long MAX_VAL_RANGE = 1000000000LL << 2LL;
const int MAX_SQRT_VAL_RANGE = 320000;

typedef long long ll;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int primes[MAX_SQRT_VAL_RANGE + 1],mu[MAX_SQRT_VAL_RANGE + 1],primeCnt;
bool isPrime[MAX_SQRT_VAL_RANGE +1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    for(int i = 2;i <= MAX_SQRT_VAL_RANGE;i++) {
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            mu[i] = -1;
        }
        for(int j = 0;j < primeCnt && i * primes[j] <= MAX_SQRT_VAL_RANGE;j++) {
            isPrime[i * primes[j]] = false;
            if(i % primes[j] == 0) {
                break;
            }else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
}

ll getRes(ll value) {
    ll result = 0;
    for(ll i = 1;i * i <= value;i++) {
        result += mu[i] * (value / (i * i));
    }
    return result;
}

int main() {
    getPrime();
    int T = read<int>();
    while(T--) {
        long long K = read<int>();
        long long left = 1,right = K << 2;
        while(left + 1 < right) {
            ll mid = (left + right) >> 1;
            if(getRes(mid) >= K) {
                right = mid;
            }else {
                left = mid;
            }
        }
        long long result = getRes(left) == K ? left : right;
        printf("%lld\n",result);
    }
    return 0;
}
