#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int *values = new int[n];
    int countOne = 0;
    for(int i = 0;i < n;i++) {
        cin >> values[i];
        if(values[i] == 1) {
            countOne++;
        }
    }
    if(countOne != 0) {
        cout << n - countOne << endl;
        return 0;
    }
    int **dp = new int*[n];
    for(int i = 0;i < n;i++) {
        dp[i] = new int[n];
        fill(dp[i],dp[i] + n,INF);
        dp[i][i] = values[i];
    }
    int countMinLen = -1;
    for(int length = 2;length <= n;length++) {
        for(int startIndex = 0;startIndex + length - 1 < n;startIndex++) {
            int endIndex = startIndex + length - 1;
            dp[startIndex][endIndex] = min(dp[startIndex][endIndex],__gcd(dp[startIndex][endIndex - 1],values[endIndex]));
            dp[startIndex][endIndex] = min(dp[startIndex + 1][endIndex],__gcd(dp[startIndex + 1][endIndex],values[startIndex]));
            if(dp[startIndex][endIndex] == 1) {
                countMinLen = length - 1;
                goto outside;
            }
        }
    }
    outside:
    if(countMinLen == -1) {
        cout << "-1" << endl;
    }else {
        cout << countMinLen + n - 1 << endl;
    }
    return 0;
}
