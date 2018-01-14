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

int main() {
    int n = read<int>();
    int *indexValues = new int[n + 1];
    indexValues[0] = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        indexValues[i + 1] = indexValues[i] ^ tmpValue;
        int maxResult = 0;
        for(int j = 0;j <= i + 1;j++) {
            maxResult = max(maxResult,indexValues[j] + (indexValues[i + 1] ^ indexValues[j]));
        }
        printf("%d\n",maxResult);
    }
    return 0;
}
