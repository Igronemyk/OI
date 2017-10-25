#include <cstdio>
#include <climits>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const long long INF = LONG_MAX;

int main() {
    int N = read<int>(),K = read<int>();
    long long *values = new long long[N + 1];
    for(int i = 0;i < N;i++) {
        values[i] = read<long long>();
    }
    values[N] = INF;
    int left = 0,right = K;
    for(int i = 0;i < N;i++) {
        while(right < N - 1 && values[right + 1] - values[i] < values[i] - values[left]) {
            left++;
            right++;
        }
        printf("%lld",(values[right] - values[i] > values[i] - values[left]) ? values[right] : values[left]);
        if(i != N - 1) printf(" ");
    }
    return 0;
}
