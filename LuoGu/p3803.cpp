#include <cstdio>
#include <algorithm>
#include <complex>
#include <cstring>
#include <cstddef>
#include <iostream>

using namespace std;

const double PI = acos(-1.0);

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

char storage[500 * 1024 * 1024];
int start = 0;

void * operator new (size_t size) {
    void * result = storage + start;
    start += size;
    return result;
}

template<typename T>
struct Complex {
    T real,image;

    Complex() : real(0) , image(0) { }
    Complex(T real,T image) : real(real) , image(image) { }

    void setReal(T val) {
        real = val;
    }

    Complex operator + (const Complex &otherComplex) const {
        return Complex(real + otherComplex.real,image + otherComplex.image);
    }

    Complex operator - (const Complex &otherComplex) const {
        return Complex(real - otherComplex.real,image - otherComplex.image);
    }

    Complex operator * (const Complex &otherComplex) const {
        return Complex(real * otherComplex.real - image * otherComplex.image,image * otherComplex.real + otherComplex.image * real);
    }

    Complex operator / (const int &otherInteger) const {
        return Complex(real / otherInteger,image / otherInteger);
    }

};

template<typename T>
Complex<T> conj(Complex<T> val) {
    return Complex<T>(val.real,-val.image);
}

struct FFT {
    int size,*bitValue;

    FFT(int size) : size(size) {
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

    void transform(Complex<double> *a,int n,int isReverse) {
        bitReverse(a,n);
        for(int length = 2;length <= n;length *= 2) {
            int mid = length / 2;
            Complex<double> wn = Complex<double>(cos(2 * PI / length),isReverse * sin(2 * PI / length));
            for(Complex<double> *pos = a;pos != a + n;pos += length) {
                Complex<double> w = Complex<double>(1,0);
                for(int i = 0;i < mid;i++) {
                    Complex<double> x = pos[i],y = pos[mid + i] * w;
                    pos[i] = x + y;
                    pos[mid + i] = x - y;
                    w = w * wn;
                }
            }
        }
    }

    void dft(Complex<double> *a,int n) {
        transform(a,n,1);
    }

    void idft(Complex<double> *a,int n) {
        transform(a,n,-1);
        for(int i = 0;i < n;i++) {
            a[i] = a[i] / n;
        }
    }

    void bitReverse(Complex<double> *a,int n) {
        for(int i = 0;i < n;i++) {
            if(bitValue[i] > i) {
                swap(a[i],a[bitValue[i]]);
            }
        }
    }

    void multiply(Complex<double> *a,Complex<double> *b,int length) {
        dft(a,length);
        dft(b,length);
        for(int i = 0;i < length;i++) {
            a[i] = a[i] * b[i];
        }
        idft(a,length);
    }

};

int main() {
    int n = read<int>(),m = read<int>();
    int length = 1;
    while(length < ((n + m + 1) << 1)) length <<= 1;
    Complex<double> *a = new Complex<double>[length],*b = new Complex<double>[length];
    for(int i = 0;i <= n;i++) {
        a[i].setReal(read<int>());
    }
    for(int i = 0;i <= m;i++) {
        b[i].setReal(read<int>());
    }
    FFT fft(length);
    fft.multiply(a,b,length);
    length = n + m + 1;
    int *result = new int[length];
    for(int i = 0;i < length;i++) {
        result[i] = static_cast<int>(round(a[i].real));
        printf("%d ",result[i]);
    }
    printf("\n");
    return 0;
}

