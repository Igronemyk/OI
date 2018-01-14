#include <cstdio>
#include <algorithm>
#include <complex>
#include <cstring>
#include <iostream>

using namespace std;

const double PI = acos(-1.0);

struct FFT {
    int size;
    complex<double> *omega,*omegaReverse;
    FFT(int size) : size(size) {
        init();
    }

    void init() {
        omega = new complex<double>[size];
        omegaReverse = new complex<double>[size];
        for(int i = 0;i < size;i++) {
            omega[i] = complex<double>(cos(2 * PI / size * i),sin(2 * PI / size * i));
            omegaReverse[i] = conj(omega[i]);
        }
    }

    void transform(complex<double> *a,int n,complex<double> *omega) {
        bitReverse(a,n);
        for(int length = 2;length <= n;length *= 2) {
            int mid = length / 2;
            for(complex<double> *pos = a;pos != a + n;pos += length) {
                for(int i = 0;i < mid;i++) {
                    complex<double> tmp = omega[n / length * i] * pos[mid + i];
                    pos[mid + i] = pos[i] - tmp;
                    pos[i] += tmp;
                }
            }
        }
    }

    void dft(complex<double> *a,int n) {
        transform(a,n,omega);
    }

    void idft(complex<double> *a,int n) {
        transform(a,n,omegaReverse);
        for(int i = 0;i < n;i++) {
            a[i] /= n;
        }
    }

    void bitReverse(complex<double> *a,int n) {
        int bitCount = 0;
        while((1 << bitCount) < n) bitCount++;
        for(int i = 0;i < n;i++) {
            int tmpValue = 0;
            for(int j = 0;j < bitCount;j++) {
                if(i & (1 << j)) {
                    tmpValue |= (1 << (bitCount - j - 1));
                }
            }
            if(i < tmpValue) swap(a[i],a[tmpValue]);
        }
    }

    void multiply(complex<double> *a,complex<double> *b,int length) {
        dft(a,length);
        dft(b,length);
        for(int i = 0;i < length;i++) {
            a[i] *= b[i];
        }
        idft(a,length);
    }

};

int main() {
    int n;
    scanf("%d",&n);
    char *s1 = new char[n + 1],*s2 = new char[n + 1];
    scanf("%s%s",s1,s2);
    int length = 1;
    while(length < (n << 1)) length <<= 1;
    complex<double> *a = new complex<double>[length],*b = new complex<double>[length];
    for(int i = 0;i < n;i++) {
        a[i].real(s1[n - i - 1] - '0');
        b[i].real(s2[n - i - 1] - '0');
    }
    FFT fft(length);
    fft.multiply(a,b,length);
    length = 2 * n;
    int *result = new int[length];
    for(int i = 0;i < length;i++) {
        result[i] = static_cast<int>(round(a[i].real()));
    }
    for(int i = 0;i < length - 1;i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }
    while(length >= 0 && result[length - 1] == 0) {
        length--;
    }
    if(length == 0) {
        printf("0\n");
    }else {
        for(int i = length - 1;i >= 0;i--) {
            printf("%d",result[i]);
        }
        printf("\n");
    }
    return 0;
}

