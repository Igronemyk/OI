#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

const int MAXN = 2010;

int values[MAXN],sum[2][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) {
        cin >> values[i];
        sum[0][i] = sum[0][i - 1] + (values[i] == 1 ? 1 : 0);
        sum[1][i] = sum[1][i - 1] + (values[i] == 2 ? 1 : 0);
    }
    int result = 0;
    for(int mid = 0;mid <= n;mid++) {
        int maxLeftValue = 0;
        for(int leftMid = 0;leftMid <= mid;leftMid++) {
            int leftFirst = sum[0][leftMid],leftSecond = sum[1][mid] - sum[1][leftMid];
            maxLeftValue = max(maxLeftValue,leftFirst + leftSecond);
        }
        int maxRightValue = 0;
        for(int rightMid = mid;rightMid <= n;rightMid++) {
            int rightFirst = sum[0][rightMid] - sum[0][mid],rightSecond = sum[1][n] - sum[1][rightMid];
            maxRightValue = max(maxRightValue,rightFirst + rightSecond);
        }
        result = max(result,maxLeftValue + maxRightValue);
    }
    cout << result << endl;
    return 0;
}


//0 ÉÏÉý1 ÏÂ½µ
/*
dp[l][r][1][1]
dp[l][r][1][2]
dp[l][r][2][1]
dp[l][r][2][2]


dp[l][r]

*/
