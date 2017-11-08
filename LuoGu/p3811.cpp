#include <cstdio>

using namespace std;

template <std::size_t bufferSize = 1U << 15>
class quick_read
{
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

int main() {
    long long n = quick_read<>::scan<int>(),p = quick_read<>::scan<int>();
    long long *inv = new long long[n + 1];
    inv[0] = -1;
    inv[1] = 1;
    printf("%lld\n",inv[1]);
    for(int i = 2;i <= n;i++) {
        //inv[i] = ((-(p / i) * inv[p % i]) % p + p) % p;
        inv[i] = ((p - p / i) * inv[p % i]) % p;
        printf("%lld\n",inv[i]);
    }
    return 0;
}
