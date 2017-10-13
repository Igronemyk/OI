#include <cstdio>

template<typename T>
inline T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int exgcd(int a,int b,int &x,int &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int result = exgcd(b,a % b,x,y);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return result;
}

int main() {
    int a = read<int>(),b = read<int>(),x = 1,y = 0;
    exgcd(a,b,x,y);
    printf("%d\n",((x % b) + b) % b);
    return 0;
}
