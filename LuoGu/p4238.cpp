#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MODDER = 998244353;
const int G = 3;
const int MAXN = 4e5 + 10;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
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
    int size;

    NTT(int size) : size(size) {}

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
        int bitCount = 0;
        while((1 << bitCount) < n) bitCount++;
        for(int i = 0;i < n;i++) {
            int tmpValue = 0;
            for(int j = 0;j < bitCount;j++) {
                if(i & (1 << j)) {
                    tmpValue |= (1 << (bitCount - j - 1));
                }
            }
            if(tmpValue > i) swap(a[i],a[tmpValue]);
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

    void getInv(long long *values,long long *tmp,long long *result,int n) {
        if(n == 1) {
            result[0] = inv(values[0]);
            return;
        }
        getInv(values,tmp,result,(n + 1) >> 1);
        int length = 1;
        while(length < (n << 1)) length <<= 1;
        copy(values,values + n,tmp);
        fill(tmp + n,tmp + length,0);
        dft(tmp,length);
        dft(result,length);
        for(int i = 0;i < length;i++) {
            result[i] = (2 - tmp[i] * result[i] % MODDER) * result[i] % MODDER;
            if(result[i] < 0) result[i] += MODDER;
        }
        idft(result,length);
        fill(result + n,result + length,0);
    }
};

long long values[MAXN],tmp[MAXN],result[MAXN];

int main() {
    int n = read<int>(),length = 1;
    while(length < (n << 1)) length <<= 1;
    for(int i = 0;i < n;i++) {
        values[i] = read<int>(); 
    }
    NTT ntt(length);
    ntt.getInv(values,tmp,result,n);
    for(int i = 0;i < n;i++) {
        printf("%lld ",result[i]);
    }
    printf("\n");
    return 0;
}
