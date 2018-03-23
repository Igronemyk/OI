#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

long long exgcd(long long a,long long b,long long &x,long long &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long result = exgcd(b,a % b,x,y);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return result;
}

int main() {
    long long a,b,c,k;
    while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&k)) {
        if(a == 0 && b == 0 && c == 0 && k == 0) break;
        long long valueB = 1LL << k;
        long long x,y;
        long long result = exgcd(c,valueB,x,y);
        long long minusValue = b - a;
        if(minusValue % result != 0) {
            printf("FOREVER\n");
            continue;
        }
        long long step = valueB / result;
        x = (x * (minusValue / result) % step + step) % step;
        printf("%lld\n",x);
    }
    return 0;
}
