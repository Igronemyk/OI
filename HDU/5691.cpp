#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_STATE = (1 << 16);
const int MAXN = 16;

int dp[MAX_STATE][MAXN],values[MAXN],pos[MAXN];

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        printf("Case #%d:\n",nowCase);
        int N = read<int>();
        int maxState = (1 << N) - 1;
        for(int i = 0;i < N;i++) {
            values[i] = read<int>();
            pos[i] = read<int>();
        }
        for(int nowState = 0;nowState <= maxState;nowState++) {
            for(int i = 0;i < N;i++) {
                dp[nowState][i] = -INF;
            }
        }
        for(int i = 0;i < N;i++) {
            if(pos[i] == -1 || pos[i] == 0) {
                dp[(1 << i)][i] = 0;
            }
        }
        for(int nowState = 0;nowState <= maxState;nowState++) {
            int countOne = 0;
            for(int i = 0;i < N;i++) {
                if((1 << i) & nowState) {
                    countOne++;
                }
            }
            for(int i = 0;i < N;i++) {
                if(!((1 << i) & nowState)) continue;
                for(int j = 0;j < N;j++) {
                    if((1 << j) & nowState) continue;
                    if(pos[j] == -1 || pos[j] == countOne) {
                        dp[nowState | (1 << j)][j] = max(dp[nowState | (1 << j)][j],dp[nowState][i] + values[i] * values[j]);
                    }
                }
            }
        }
        int result = -INF;
        for(int i = 0;i < N;i++) {
            result = max(result,dp[maxState][i]);
        }
        printf("%d\n",result);
    }
    return 0;
}
