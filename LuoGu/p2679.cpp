#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


long long dp[2][210][210][2];

const int MODDER = (int)(1e9 + 7);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N,M,K;
    cin >> N >> M >> K;
    string A,B;
    cin >> A >> B;
    if(K == 1) {
        int result = 0;
        int pos = A.find(B);
        while(pos != -1) {
            result++;
            pos = A.find(B,pos + 1);
        }
        cout << result << endl;
    }else {
        dp[0][0][0][0] = 1;
        dp[1][0][0][0] = 1;
        for(int i = 1;i <= N;i++) {
            int nowIndex = (i & 1),preIndex = !nowIndex;
            for(int j = 1;j <= M;j++) {
                for(int k = 1;k <= K;k++) {
                    if(A[i - 1] == B[j - 1]) {
                        dp[nowIndex][j][k][1] = (dp[preIndex][j - 1][k][1] + dp[preIndex][j - 1][k - 1][0] + dp[preIndex][j - 1][k - 1][1]) % MODDER;
                    }else {
                        dp[nowIndex][j][k][1] = 0;
                    }
                    dp[nowIndex][j][k][0] = (dp[preIndex][j][k][0] + dp[preIndex][j][k][1]) % MODDER;
                }
            }
        }
        cout << (dp[N & 1][M][K][1] + dp[N & 1][M][K][0]) % MODDER << endl;
    }
    return 0;
}
