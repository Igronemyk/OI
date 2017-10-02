#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int counter[101],hasValue[101];

int main(){
    int n = read<int>();
    int nowValues = 0;
    for(int i = 0;i < n;i++){
        int tmpValue = read<int>();
        if(counter[tmpValue] == 0) hasValue[nowValues++] = tmpValue;
        counter[tmpValue]++;
    }
    if(nowValues != 2){
        printf("NO\n");
    }else if(counter[hasValue[0]] != counter[hasValue[1]]){
        printf("NO\n");
    }else{
        printf("YES\n%d %d\n",hasValue[0],hasValue[1]);
    }
    return 0;
}
