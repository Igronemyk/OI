#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    long long sumValue = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        sumValue += tmpValue;
    }
    long long maxValue1 = 0,maxValue2 = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue > maxValue1) {
            maxValue2 = maxValue1;
            maxValue1 = tmpValue;
        }else if(tmpValue > maxValue2) {
            maxValue2 = tmpValue;
        }
    }
    if(maxValue1 + maxValue2 >= sumValue) {
        cout << "YES" << endl;
    }else {
        cout << "NO" << endl;
    }
    return 0;
}
