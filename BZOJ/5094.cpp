#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int N_VAL[] = {10,100,1000,10000,100000,1000000,10000000};

int main() {
    int m = read<int>();
    unsigned long long *values = new unsigned long long[m + 1];
    for(int i = 0;i < m;i++) {
        values[i] = read<unsigned long long>();
    }
    sort(values,values + m);
    int result = unique(values,values + m) - values;
    printf("%d\n",*lower_bound(N_VAL,N_VAL + 7,result));
    return 0;
}
