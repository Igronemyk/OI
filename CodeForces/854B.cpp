#include <cstdio>
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
    int n = read<int>(), k = read<int>();
    if(n == k){
        printf("0 0\n");
    }else if(k == 0){
        printf("0 0\n");
    }else{
        printf("1 ");
        int cutLength = min(k,n / 3);
        int result = cutLength * 2;
        k -= cutLength;
        n -= cutLength * 3;
        bool flag = false;
        if(k != 0 && n == 2){
            k--;
            n = 0;
            result++;
        }else if(k != 0 && n == 1){
            flag = true;
        }
        result -= k;
        printf("%d\n",result + (flag ? 1 : 0));
    }
    return 0;
}
