#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    long long sumValue = (1 + n) * 1LL * n / 2;
    if(sumValue % 2 == 0) {
        cout << 0 << endl;
    }else {
        cout << 1 << endl;
    }
    long long targetValue = sumValue / 2,nowValue = 0,selectValue = n;
    queue<long long> result;
    while(targetValue - nowValue > n) {
        nowValue += selectValue;
        result.push(selectValue);
        selectValue--;
    }
    if(targetValue - nowValue != 0) {
        long long leftValue = targetValue - nowValue;
        if(selectValue >= leftValue) {
            result.push(leftValue);
        }else {
            result.push(selectValue);
            result.push(leftValue - selectValue);
        }
    }
    cout << result.size() << " ";
    while(!result.empty()) {
        long long tmpValue = result.front();
        result.pop();
        cout << tmpValue << " ";
    }
    cout << endl;
    return 0;
}
//14
