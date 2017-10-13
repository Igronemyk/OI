#include <cstdio>
#include <cstring>

int value[100001];

template<typename T>
inline T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}


int main(){
    int N;
    while((N = read<int>()) != 0){
        memset(value,0,sizeof(value));
        for(int i = 0;i < N;i++){
            value[read<int>()]++;
            value[read<int>() + 1]--;
        }
        int tmpValue = 0;
        for(int i = 1;i <= N;i++){
            tmpValue += value[i];
            printf("%d",tmpValue);
            if(i != N) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
