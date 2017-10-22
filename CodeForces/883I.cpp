#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    int *values = new int[n + 1];
    for(int i = 0;i < n;i++) {
        cin >> values[i];
    }
    int result = 0;
    sort(values,values + n);
    values[n] = INF;
    int pos = 0;
    while(true) {
        if(pos + 2 * k - 1 > n - 1) {
            break;
        }
        int minValue = INF,maxValue = 0;
        for(int i = pos;i < pos + k;i++) {
            minValue = min(minValue,values[i]);
            maxValue = max(maxValue,values[i]);
        }
        pos += k;
        while(values[pos] == values[pos - 1]) {
            pos++;
        }
        result = max(result,maxValue - minValue);
    }
    int minValue = INF,maxValue = 0;
    for(int i = pos;i <= n - 1;i++) {
        minValue = min(minValue,values[i]);
        maxValue = max(maxValue,values[i]);
    }
    result = max(result,maxValue - minValue);
    cout << result << endl;
    return 0;
}
