#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 10;
const int MAXM = 10;
const int MAX_STATE = (1 << (MAXN + MAXM));
const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int lowbit(int value) {
    return value & -value;
}

int countOne(int value) {
    int result = 0;
    while(value) {
        result++;
        value -= lowbit(value);
    }
    return result;
}

int n,m,values[2][MAXN + 1][MAXM + 1],dp[MAX_STATE];

int countDone(int value) {
    int result = 0;
    int nowValue = n;
    for(int i = 0;i < n + m;i++) {
        if((value >> i) & 1) {
            nowValue--;
        }else {
            result += nowValue;
        }
    }
    return result;
}

int main() {
    n = read<int>(); m = read<int>();
    for(int i = 0;i < 2;i++) {
        for(int j = 1;j <= n;j++) {
            for(int k = 1;k <= m;k++) {
                values[i][j][k] = read<int>();
            }
        }
    }
    int startState = ((1 << n) - 1) << m,endState = (1 << n) - 1;
    dp[startState] = 0;
    for(int nowState = startState - 1;nowState >= endState;nowState--) {
        if(countOne(nowState) != n) continue;
        int nowPerson = countDone(nowState) & 1,result;
        if(nowPerson) {
            result = INF;
            int nowX = n,nowY = 0;
            for(int i = 0;i < n + m;i++) {
                if((nowState >> i) & 1) {
                    nowX--;
                }else {
                    nowY++;
                }
                if((i + 1 < n + m) && ((nowState >> i) & 1) && !((nowState >> (i + 1)) & 1)) {
                    result = min(result,dp[nowState ^ (1 << i) ^ (1 << (i + 1))] - values[1][nowX + 1][nowY + 1]);
                }
            }
        }else {
            result = -INF;
            int nowX = n,nowY = 0;
            for(int i = 0;i < n + m;i++) {
                if((nowState >> i) & 1) {
                    nowX--;
                }else {
                    nowY++;
                }
                if((i + 1 < n + m) && ((nowState >> i) & 1) && !((nowState >> (i + 1)) & 1)) {
                    result = max(result,dp[nowState ^ (1 << i) ^ (1 << (i + 1))] + values[0][nowX + 1][nowY + 1]);
                 }
            }
        }
        dp[nowState] = result;
    }
    printf("%d\n",dp[endState]);
    return 0;
}
