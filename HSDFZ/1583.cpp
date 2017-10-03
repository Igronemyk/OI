#include <cstdio>
#include <algorithm>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int *value;

int main(){
    int W = read<int>(),n = read<int>();
    value = new int[n];
    for(int i = 0;i < n;i++) value[i] = read<int>();
    std::sort(value,value + n);
    int startPos = 0,endPos = n - 1;
    int result = 0;
    while(startPos < endPos){
        if(value[startPos] + value[endPos ] <= W){
            startPos++;
        }
        endPos--;
        result++;
    }
    if(startPos == endPos) result++;
    printf("%d\n",result);
    return 0;
}
