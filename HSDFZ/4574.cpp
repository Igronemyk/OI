#include <cstdio>

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}


bool visit[110];


int main() {
    int n = read<int>();
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        if(!visit[tmpValue]) {
            visit[tmpValue] = true;
            printf("%d ",tmpValue);
        }
    }
    return 0;
}
