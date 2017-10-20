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

struct Data{
    int front,back;
    Data() : front(-1) , back(-1) { }
    Data(int front,int back) : front(front) , back(back) { }
};

int main() {
    int N = read<int>();
    Data *datas = new Data[2 * N];
    for(int i = 0;i < N;i++) {
        int reIndex = i - 1;
        if(reIndex < 0) reIndex += N;
        datas[i].front = read<int>();
        datas[reIndex].back = datas[i].front;
    }
    for(int i = 0;i < N;i++) {
        datas[i + N] = datas[i];
    }
    int **dp = new int*[N + 1];
    for(int i = 0;i <= N;i++) {
        dp[i] = new int[2 * N];
        memset(dp[i],0,sizeof(int) * 2 * N);
    }
    for(int len = 2;len <= N;len++) {
        for(int left = 0;left <= 2 * N - len;left++) {
            int right = left + len - 1;
            for(int cutPoint = left;cutPoint < right;cutPoint++) {
                dp[len][left] = max(dp[len][left],dp[cutPoint - left + 1][left] + dp[right - cutPoint][cutPoint + 1] + datas[left].front * datas[cutPoint].back * datas[right].back);
            }
        }
    }
    int result = 0;
    for(int i = 0;i < N;i++) {
        result = max(result,dp[N][i]);
    }
    printf("%d\n",result);
    return 0;
}
