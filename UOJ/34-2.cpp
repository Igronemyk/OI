#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MODDER = 998244353;
const int G = 3;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long quickPow(long long a,int b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % MODDER;
        base = (base * base) % MODDER;
        b >>= 1;
    }
    return result;
}

long long inv(long long value) {
    return quickPow(value,MODDER - 2);
}

struct NTT {
    int size,*bitValue;

    NTT(int size) : size(size) {
        init();
    }

    void init() {
        bitValue = new int[size];
        int bitCount = 0;
        while((1 << bitCount) < size) bitCount++;
        for(int i = 0;i < size;i++) {
            int tmpValue = 0;
            for(int j = 0;j < bitCount;j++) {
                if(i & (1 << j)) {
                    tmpValue |= (1 << (bitCount - j - 1));
                }
            }
            bitValue[i] = tmpValue;
        }
    }

    void transform(long long *a,int n,bool isReverse) {
        bitReverse(a,n);
        long long baseW = quickPow(G,(MODDER - 1) / n);
        if(isReverse) {
            baseW = inv(baseW);
        }
        for(int length = 2;length <= n;length <<= 1) {
            int mid = length / 2;
            long long wn = quickPow(baseW,n / length);
            for(long long *pos = a;pos != a + n;pos += length) {
                long long w = 1;
                for(int i = 0;i < mid;i++) {
                    long long x = pos[i],y = pos[mid + i] * w % MODDER;
                    pos[i] = (x + y) % MODDER;
                    pos[mid + i] = (x - y + MODDER) % MODDER;
                    w = (w * wn) % MODDER;
                }
            }
        }
    }

    void dft(long long *a,int n) {
        transform(a,n,false);
    }

    void idft(long long *a,int n) {
        transform(a,n,true);
        int x = inv(n);
        for(int i = 0;i < n;i++) {
            a[i] = (a[i] * x) % MODDER;
        }
    }

    void bitReverse(long long *a,int n) {
        for(int i = 0;i < n;i++) {
            if(bitValue[i] > i) {
                swap(a[i],a[bitValue[i]]);
            }
        }
    }

    void multiply(long long *a,long long *b,int length) {
        dft(a,length);
        dft(b,length);
        for(int i = 0;i < length;i++) {
            a[i] = (a[i] * b[i]) % MODDER;
        }
        idft(a,length);
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    int length = 1;
    while(length < n + m + 2) length <<= 1;
    long long *a = new long long[length],*b = new long long[length];
    memset(a,0,sizeof(long long) * length);
    memset(b,0,sizeof(long long) * length);
    for(int i = 0;i <= n;i++) {
        a[i] = read<int>();
    }
    for(int i = 0;i <= m;i++) {
        b[i] = read<int>();
    }
    NTT ntt(length);
    ntt.multiply(a,b,length);
    length = n + m + 1;
    for(int i = 0;i < length;i++) {
        printf("%lld ",a[i]);
    }
    printf("\n");
    return 0;
}
