#include <cstdio>

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>();
    int prev = read<int>(),direction = 0,result = 1;
    for(int i = 1;i < n;i++){
        int value = read<int>();
        if(value == prev) continue;
        if(direction == 0){
            result++;
            direction = value > prev ? 1 : -1;
            prev = value;
            continue;
        }
        if(direction == 1 && value < prev){
            result++;
            direction = -1;
        }else if(direction == -1 && value > prev){
            result++;
            direction = 1;
        }
        prev = value;
    }
    printf("%d\n",result);
    return 0;
}
