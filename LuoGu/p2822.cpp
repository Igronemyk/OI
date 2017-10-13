#include <cstdio>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int value[2010][2010],prevValue[2010][2010];

int main(){
    int t = read<int>(),k = read<int>();
    for(int i = 1;i <= 2000;i++){
        value[i][0] = 1;
        value[i][i] = 1;
    }
    for(int i = 2;i <= 2000;i++){
        for(int j = 1;j < i;j++){
            value[i][j] = (value[i - 1][j] + value[i - 1][j - 1]) % k;
        }
    }
    for(int i = 1;i <= 2000;i++){
        for(int j = 1;j <= 2000;j++){
            prevValue[i][j] = prevValue[i - 1][j] + prevValue[i][j - 1] - prevValue[i - 1][j - 1];
            if(value[i][j] == 0 && j < i){
                prevValue[i][j]++;
            }
        }
    }
    while(t--){
        int n = read<int>(),m = read<int>();
        printf("%d\n",prevValue[n][m]);
    }
    return 0;
}
