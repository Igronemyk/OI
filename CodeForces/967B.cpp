#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,A,B;
    cin >> n >> A >> B;
    int value;
    cin >> value;
    multiset<int> values;
    int sumValue = value;
    for(int i = 2;i <= n;i++) {
        int tmpValue;
        cin >> tmpValue;
        sumValue += tmpValue;
        values.insert(tmpValue);
    }
    int cnt = 0;
    while(true) {
        double limit = value * 1.00 / sumValue * A;
        if(limit < B) {
            int maxValue = *values.rbegin();
            values.erase(--values.end());
            sumValue -= maxValue;
            cnt++;
        }else {
            break;
        }
    }
    cout << cnt << endl;
    return 0;
}

