#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int T = read<int>();
    while(T--) {
        long long p = read<long long>(),a = read<long long>(),b = read<long long>(),X1 = read<long long>(),t = read<long long>();
        long long sqrtValue = static_cast<long long>(ceil(sqrt(p)));
        map<long long,long long> values;
        if(X1 == t) {
            printf("1\n");
            continue;
        }else if(a == 0) {
            if(b == t) {
                printf("2\n");
            }else {
                printf("-1\n");
            }
            continue;
        }
        long long reA = 1,reB = 0;
        for(int i = 1;i <= sqrtValue;i++) {
            reA = reA * a % p;
            reB = (a * reB + b) % p;
        }
        long long now = t;
        for(int i = 0;i <= sqrtValue;i++) {
            if(values.count(now) == 0) {
                values[now] = i;
            }
            now = (a * now + b) % p;
        }
        now = (reA * X1 + reB) % p;
        bool sign = false;
        for(int i = 1;i <= sqrtValue;i++) {
            if(values.count(now) != 0) {
                printf("%lld\n",1 + i * sqrtValue - values[now]);
                sign = true;
                break;
            }
            now = (reA * now + reB) % p;
        }
        if(!sign) {
            printf("-1\n");
        }
    }
    return 0;
}
