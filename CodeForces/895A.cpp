#include <iostream>
#include <algorithm>

using namespace std;

int n;

int getResult(int *values) {
    int *indexValues = new int[n + 1];
    indexValues[0] = 0;
    for(int i = 0;i < n;i++) {
        indexValues[i + 1] = indexValues[i] + values[i];
    }
    int *reIndexValues = new int[n + 1];
    reIndexValues[n] = 0;
    for(int i = n - 1;i >= 0;i--) {
        reIndexValues[i] = reIndexValues[i + 1] + values[i];
    }
    int result = 360;
    for(int i = 0;i <= n;i++) {
        if(abs(indexValues[i] - reIndexValues[i]) < result) {
            result = abs(indexValues[i] - reIndexValues[i]);
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        cin >> values[i];
    }
    int result = 360;
    for(int i = 0;i < n;i++) {
        int tmpValue = values[0];
        for(int j = 0;j < n - 1;j++) {
            values[j] = values[j + 1];
        }
        values[n - 1] = tmpValue;
        result = min(result,getResult(values));
    }
    cout << result << endl;
    return 0;
}
