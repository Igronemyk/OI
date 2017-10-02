#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main(){
    int a = read<int>(),b = read<int>(),f = read<int>(),k = read<int>();
    int firstCount = f,secondCount = a - f;
    if(b < firstCount || b < secondCount) {
        printf("-1\n");
        return 0;
    }
    if(k == 1){
        printf("%d\n",b < a ? 1 : 0);
        return 0;
    }
    int firstValue = secondCount * 2,secondValue = firstCount * 2,nowRound = 1,nowFuel = b - firstCount,result = 0;
    while(nowRound < k){
        int nowValue = (nowRound & 1) ? firstValue : secondValue;
        if(nowFuel < nowValue){
            nowFuel = b;
            result++;
        }
        if(nowFuel < nowValue){
            printf("-1\n");
            return 0;
        }
        nowFuel -= nowValue;
        nowRound++;
    }
    printf("%d\n",result + ((nowFuel < ((k & 1) ? secondCount : firstCount)) ? 1 : 0));
    return 0;
}
