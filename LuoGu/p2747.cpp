#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N,V;
    cin >> N >> V;
    bool **hasRoad = new bool*[N];
    for(int i = 0;i < N;i++) {
        hasRoad[i] = new bool[N];
        memset(hasRoad[i],false,sizeof(bool) * N);
    }
    map<string,int> cityIndex;
    int indexValue = 0;
    for(int i = 0;i < N;i++) {
        string city;
        cin >> city;
        cityIndex[city] = indexValue++;
    }
    while(V--) {
        string from,to;
        cin >> from >> to;
        int fromIndex = cityIndex[from],toIndex = cityIndex[to];
        hasRoad[fromIndex][toIndex] = true;
        hasRoad[toIndex][fromIndex] = true;
    }
    int **dp = new int*[N];
    for(int i = 0;i < N;i++) {
        dp[i] = new int[N];
        memset(dp[i],0,sizeof(int) * N);
    }
    dp[0][0] = 1;
    for(int i = 0;i < N;i++) {
        for(int j = i + 1;j < N;j++) {
            for(int k = 0;k < j;k++) {
                if(!hasRoad[j][k] || dp[i][k] == 0) continue;
                dp[i][j] = max(dp[i][j],dp[i][k] + 1);
                dp[j][i] = max(dp[i][j],dp[j][i]);
            }
        }
    }
    int result = 1;
    for(int i = 0;i < N;i++) {
        if(!hasRoad[i][N - 1]) continue;
        result = max(result,dp[i][N - 1]);
    }
    cout << result << endl;
    return 0;
}
