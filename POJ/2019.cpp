#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>(),B = read<int>(),K = read<int>();
    int **values = new int*[N];
    for(int i = 0;i < N;i++) {
        values[i] = new int[N];
        for(int j = 0;j < N;j++) {
            values[i][j] = read<int>();
        }
    }
    while(K--) {
        int row = read<int>(),col = read<int>(),minValue = INF,maxValue = -INF;
        row--; col--;
        for(int i = row;i <= row + B - 1;i++) {
            for(int j = col;j <= col + B - 1;j++) {
                minValue = min(minValue,values[i][j]);
                maxValue = max(maxValue,values[i][j]);
            }
        }
        printf("%d\n",maxValue - minValue);
    }
    return 0;
}
