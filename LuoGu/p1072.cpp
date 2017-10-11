#include <cstdio>

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int gcd(int a,int b){
    while(b){
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main(){
    int n = read<int>();
    while(n--){
        int result = 0;
        int a0 = read<int>(),a1 = read<int>(),b0 = read<int>(),b1 = read<int>();
        for(int i = 1;i * i <= b1;i++){
            if(b1 % i != 0) continue;
            if(i % a1 == 0 && gcd(a0 / a1,i / a1) == 1 && gcd(b1 / b0,b1 / i) == 1) result++;
            int j = b1 / i;
            if(i == j) continue;
            if(j % a1 == 0 && gcd(a0 / a1,j / a1) == 1 && gcd(b1 / b0,b1 / j) == 1) result++;
        }
        printf("%d\n",result);
    }
    return 0;
}
