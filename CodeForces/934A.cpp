#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    long long *first = new long long[n],*second = new long long[m];
    for(int i = 0;i < n;i++) {
        cin >> first[i];
    }
    for(int i = 0;i < m;i++) {
        cin >> second[i];
    }
    long long result = INF;
    for(int banned = 0;banned < n;banned++) {
        long long tmpResult = -INF;
        for(int i = 0;i < n;i++) {
            if(i == banned) continue;
            for(int j = 0;j < m;j++) {
                tmpResult = max(tmpResult,first[i] * second[j]);
            }
        }
        result = min(result,tmpResult);
    }
    cout << result << endl;
    return 0;
}
