#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    long long a = read<long long>(),b = read<long long>();
    if(b - a >= 10){
        printf("0\n");
    }else if((a % 10) > (b % 10)){
        printf("0\n");
    }else{
        a = a % 10;b = b % 10;
        int result = 1;
        for(int i = a + 1;i <= b;i++){
            result *= i;
        }
        printf("%d\n",result % 10);
    }
    return 0;
}

