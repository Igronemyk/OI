#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N,M;
    while(~scanf("%d%d",&N,&M)) {
        pair<int,int> *stk = new pair<int,int>[N + 1];
        int *values = new int[N + 1],nowPos = 0;
        int *sumValues = new int[N + 1],*dp = new int[N + 1];
        stk[0] = make_pair(1,1);
        sumValues[0] = 0;
        dp[1] = 1;
        for(int i = 1;i <= N;i++) {
            values[i] = read<int>();
            sumValues[i] = sumValues[i - 1] + values[i];
        }
        for(int i = 2;i <= N;i++) {

        }
        delete[] stk;
        delete[] values;
        delete[] sumValues;
        delete[] dp;
    }
    return 0;
}
