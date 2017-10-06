#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int n = read<int>(),x = read<int>();
    if(n == 1){
        printf("YES\n%d\n",x);
    }else if(n == 2 && x == 0){
        printf("NO\n");
    }else if(n == 2){
        printf("YES\n%d %d\n",0,x);
    }else{
        printf("YES\n");
        int ans = 0,maxValue1 = 1 << 17,maxValue2 = 1 << 18;
        for(int i = 1;i <= n - 3;i++){
            printf("%d ",i);
            ans ^= i;
        }
        if(ans == x){
            printf("%d %d %d\n",maxValue1 | maxValue2,maxValue1,maxValue2);
        }else{
            printf("%d %d %d\n",maxValue1,(maxValue1^ans)^x,0);
        }
    }
    return 0;
}
