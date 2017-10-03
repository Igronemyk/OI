#include <cstdio>
#include <algorithm>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int N = read<int>(),K = read<int>();
    int *value = new int[N];
    for(int i = 0;i < N;i++) value[i] = read<int>();
    std::nth_element(value,value + K - 1,value + N);
    printf("%d\n",value[K - 1]);
    return 0;
}
