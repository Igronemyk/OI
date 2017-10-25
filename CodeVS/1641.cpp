#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int values[100][100];

int main() {
    /*
    int N = read<int>(),K = read<int>();
    long long M = read<long long>();
    */
    values[0][0] = 1;
    for(int i = 1;i <= 30;i++) {
        values[0][i] = 1;
        values[i][0] = 1;
    }
    for(int i = 1;i <= 30;i++) {
        for(int j = 1;j <= 30;j++) {
            if(j > i) {
                values[i][j] = values[i][j - 1];
                continue;
            }
            values[i][j] = values[i - 1][j - 1] + values[i - 1][j];
        }
    }
    for(int i = 0;i <= 30;i++) {
        for(int j = 0;j <= 30;j++) {
            printf("%d ",values[i][j]);
        }
        printf("\n");
    }
    return 0;
}
