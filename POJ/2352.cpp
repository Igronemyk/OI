#include <cstdio>
#include <cstring>

template<typename T>
inline T read(){
    T result = 0;bool f = 1;char c = getchar();
    while( c >'9' ||c <'0') {if(c == '-') f *= -1; c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = 32010;

int value[MAXN],result[MAXN],N;

int lowbit(int val){
    return val & -val;
}

void update(int x,int val){
    for(int i = x;i <= MAXN;i += lowbit(i)){
        value[i] += val;
    }
}

int getSum(int x){
    int result = 0;
    for(int i = x;i > 0;i -= lowbit(i)){
        result += value[i];
    }
    return result;
}

int main(){
    while(~scanf("%d",&N)){
        memset(value,0,sizeof(value));
        memset(result,0,sizeof(result));
        for(int i = 0;i < N;i++){
            int x = read<int>(),y = read<int>();
            x++;y++;
            result[getSum(x)]++;
            update(x,1);
        }
        for(int i = 0;i < N;i++){
            printf("%d\n",result[i]);
        }
    }
    return 0;
}
