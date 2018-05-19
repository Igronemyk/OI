#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 50;
const int MAX_DEPTH = 51;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LinearBase {
    long long values[MAX_DEPTH + 1];

    LinearBase() {
        memset(values,0,sizeof(values));
    }

    void insert(long long value) {
        for(int i = MAX_DEPTH;i >= 0;i--) {
            if(!((value >> i) & 1)) continue;
            if(values[i] == 0) {
                values[i] = value;
                break;
            }else {
                value ^= values[i];
            }
        }
    }

    long long getMaxXorValue() {
        long long value = 0;
        for(int i = MAX_DEPTH;i >= 0;i--) {
            if((value ^ values[i]) > value) {
                value ^= values[i];
            }
        }
        return value;
    }
} linearBase;

int main() {
    int n = read<int>();
    for(int i = 1;i <= n;i++) {
        long long value = read<long long>();
        linearBase.insert(value);
    }
    printf("%lld\n",linearBase.getMaxXorValue());
    return 0;
}
