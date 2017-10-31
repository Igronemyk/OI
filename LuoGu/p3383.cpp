#include <cstdio>
#include <cstring>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = static_cast<int>(1e7 + 1);

bool isPrime[MAXN];
int prime[MAXN];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    int countVal = 0;
    isPrime[1] = false;
    for(int i = 2;i < MAXN;i++) {
        if(isPrime[i]) {
            prime[countVal++] = i;
        }
        for(int j = 0;j < countVal && i * prime[j] < MAXN;j++) {
            isPrime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

int main() {
    getPrime();
    int N = read<int>(),M = read<int>();
    while(M--) {
        printf(isPrime[read<int>()] ? "Yes\n" : "No\n");
    }
    return 0;
}
