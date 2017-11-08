#include <cstdio>

const int MAXN = 450;
const int MAXM = 450;

template <typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == ' ') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long indexValue[MAXN][MAXM];

int main() {
    int n = read<int>(),m = read<int>(),k = read<int>();
    long long result = 0;
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            long long tmpValue = read<long long>();
            tmpValue %= k;
            indexValue[i][j] = (index[i][j - 1] + index[i - 1][j] - index[i - 1][j - 1] + tmpValue) % k;
            if(indexValue[i][j] < 0) {
                indexValue[i][j] += k;
            }
        }
    }

    return 0;
}
