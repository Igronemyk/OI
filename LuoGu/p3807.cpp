#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_VAL = 1e5;

template <std::size_t bufferSize = 1U << 15>
class quick_read {
public:
    static std::size_t buffer_size() {
        return bufferSize;
    }

    static int getchar() {
        if (S == T)
        {
            S = buffer;
            T = buffer + std::fread(buffer, 1, buffer_size(), stdin);
            if (S == T)
            {
                return EOF;
            }
        }
        return *S++;
    }

    template <typename Integer>
    static Integer scan() {
        char c = getchar();
        Integer result = 0;
        int f = 1;
        while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
        while(c <= '9' && c >= '0') {result = result * 10 + c- '0';c = getchar();}
        return result * f;
    }
private:
    static char buffer[bufferSize];
    static char *S;
    static char *T;
};

template <std::size_t bufferSize>
char quick_read<bufferSize>::buffer[bufferSize];

template <std::size_t bufferSize>
char *quick_read<bufferSize>::S = NULL;

template <std::size_t bufferSize>
char *quick_read<bufferSize>::T = NULL;

int fac[MAX_VAL + 1];

int quickPow(int a,int b,int p) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    return result;
}

int inv(int val,int p) {
    return quickPow(val,p - 2,p);
}

int comb(int n,int m,int p) {
    if(m > n) return 0;
    return (fac[n] * 1LL * inv((fac[m] * 1LL * fac[n - m]) % p,p)) % p;
}

int lucas(int n,int m,int p) {
    if(m == 0) return 1;
    return (lucas(n / p,m / p,p) * 1LL * comb(n %p,m % p,p)) % p;
}

int main() {
    int T = quick_read<>::scan<int>();
    fac[0] = 1;
    while(T--) {
        int n = quick_read<>::scan<int>(),m = quick_read<>::scan<int>(),p = quick_read<>::scan<int>();
        for(int i = 1;i <= p;i++) {
            fac[i] = (fac[i - 1] * 1LL * i) % p;
        }
        printf("%d\n",lucas(n + m,m,p));
    }
    return 0;
}
