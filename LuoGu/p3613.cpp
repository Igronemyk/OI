#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int BUFFER_SIZE = 4;
const int MAX_BIT = 30;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool hasBit(const int &value,const int bit) {
    return (value >>bit) & 1;
}

int main() {
    int n = read<int>(),m = read<int>(),val1 = 0,val2 = INT_MAX;
    char *buffer = new char[BUFFER_SIZE];
    for(int i = 1;i <= n;i++) {
        scanf("%s",buffer);
        int t = read<int>();
        if(buffer[0] == 'O') {
            val1 |= t;
            val2 |= t;
        }else if(buffer[0] == 'X') {
            val1 ^= t;
            val2 ^= t;
        }else if(buffer[0] == 'A') {
            val1 &= t;
            val2 &= t;
        }
    }
    int result = 0;
    for(int i = MAX_BIT;i >= 0;i--) {
        if(hasBit(val1,i)) {
            result |= (1 << i);
        }else if(hasBit(val2,i) && m >= (1 << i)) {
            result |= (1 << i);
            m -= (1 << i);
        }
    }
    printf("%d\n",result);
    return 0;
}
