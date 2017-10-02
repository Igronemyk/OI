#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>();
    int maxValue = 0,nowValue = 0;
    for(int i = 0;i < n;i++){
        int tmpValue = read<int>();
        nowValue = nowValue < 0 ? tmpValue : tmpValue + nowValue;
        if(nowValue > maxValue) maxValue = nowValue;
    }
    printf("%d\n",maxValue);
    return 0;
}
