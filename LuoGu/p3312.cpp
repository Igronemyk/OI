#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXQ = 2e4 + 10;
const long long MODDER = (1LL << 31);

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long primes[MAXN + 1],mu[MAXN + 1],simga[MAXN + 1],primeCnt;
bool isPrime[MAXN + 1];

void getPrime() {
    memset(isPrime,true,sizeof(isPrime));
    isPrime[1] = false;
    mu[1] = 1;
    simga[1] = 1;
    for(int i = 2;i <= MAXN;i++) {
        if(isPrime[i]) {
            primes[primeCnt++] = i;
            mu[i] = -1;
            simga[i] = i + 1;
        }
        for(int j = 0;j < primeCnt && i * primes[j] <= MAXN;j++) {
            isPrime[i * primes[j]] = false;
            long long tmpValue = i;
            while(tmpValue % primes[j] == 0) tmpValue /= primes[j];
            simga[i * primes[j]] = simga[i] * primes[j] + simga[tmpValue];
            if(i % primes[j] == 0) {
                break;
            }else {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
}

template<typename T>
struct BIT {
    T values[MAXN + 1];

    BIT() {
        memset(values,0,sizeof(values));
    }

    void update(int pos,T value) {
        for(int i = pos;i <= MAXN;i += lowbit(i)) {
            values[i] += value;
        }
    }

    T getSum(int pos) {
        T result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }


    int lowbit(int value) {
        return value & -value;
    }
};

BIT<long long> bitree;

struct Info {
    int n,m,a,sign;

    bool operator < (const Info &tmpInfo) const {
        return a < tmpInfo.a;
    }
} infos[MAXQ];

int simgaSign[MAXN + 1];

bool comp(const int &a,const int &b) {
    return simga[a] < simga[b];
}

long long results[MAXQ];

int main() {
    getPrime();
    int T = read<int>();
    for(int i = 0;i < T;i++) {
        infos[i].n = read<int>();
        infos[i].m = read<int>();
        infos[i].a = read<int>();
        infos[i].sign = i;
    }
    sort(infos,infos + T);
    for(int i = 1;i <= MAXN;i++) {
        simgaSign[i] = i;
    }
    sort(simgaSign + 1,simgaSign + MAXN + 1,comp);
    int nowSign = 1;
    for(int nowCase = 0;nowCase < T;nowCase++) {
        Info &tmpInfo = infos[nowCase];
        while(nowSign <= MAXN && simga[simgaSign[nowSign]] <= tmpInfo.a) {
            for(int i = 1;i * simgaSign[nowSign] <= MAXN;i++) {
                bitree.update(i * simgaSign[nowSign],simga[simgaSign[nowSign]] * mu[i]);
            }
            nowSign++;
        }
        int limit = min(tmpInfo.n,tmpInfo.m);
        for(int i = 1;i <= limit;i++) {
            int jumpTo = min(tmpInfo.n / (tmpInfo.n / i),tmpInfo.m / (tmpInfo.m / i));
            results[tmpInfo.sign] += (bitree.getSum(jumpTo) - bitree.getSum(i - 1)) * (tmpInfo.n / i) * (tmpInfo.m / i);
            i = jumpTo;
        }
    }
    for(int i = 0;i < T;i++) {
        printf("%lld\n",results[i] % MODDER);
    }
    return 0;
}
