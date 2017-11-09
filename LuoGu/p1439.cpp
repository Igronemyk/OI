#include <cstdio>
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
    int *reIndex = new int[n + 1];
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        reIndex[tmpValue] = i;
    }
    int *values = new int[n + 1];
    int nowCnt = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue = reIndex[read<int>()];
        int *pos = lower_bound(values,values + nowCnt,tmpValue);
        if(pos == values + nowCnt) {
            values[nowCnt++] = tmpValue;
        }else {
            *pos = tmpValue;
        }
    }
    printf("%d\n",nowCnt);
    return 0;
}
