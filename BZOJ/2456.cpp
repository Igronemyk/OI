#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int n = read<int>(),cnt = 1;
    long long val = read<long long>();
    for(int i = 1;i < n;i++) {
        long long tmpVal = read<long long>();
        if(val == tmpVal) {
            cnt++;
        }else if(cnt > 0) {
            cnt--;
        }else {
            val = tmpVal;
            cnt = 1;
        }
    }
    printf("%lld\n",val);
    return 0;
}
