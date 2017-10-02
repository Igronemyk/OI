#include <cstdio>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>(),k = read<int>();
    for(int i = 0;i < n;i++){
        long long tmpValue = read<long long>();

    }
    return 0;
}
