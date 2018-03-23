#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

const int MAX_VALUE = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    if(n == 1) {
        cout << "YES" << endl;
        cout << MAX_VALUE << " " << MAX_VALUE << endl;
        return 0;
    }
    vector<int> values;
    int lastValue;
    cin >> lastValue;
    set<int> minuss;
    values.push_back(lastValue);
    for(int i = 1;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        minuss.insert(abs(tmpValue - lastValue));
        lastValue = tmpValue;
        values.push_back(tmpValue);
    }
    minuss.erase(1);
    if(minuss.size() > 1) {
        cout << "NO" << endl;
        return 0;
    }else if(minuss.size() == 0) {
        cout << "YES" << endl;
        cout << MAX_VALUE << " " << 1 << endl;
        return 0;
    }
    int y = *minuss.begin();
    if(y == 0) {
        cout << "NO" << endl;
        return 0;
    }
    bool flag = true;
    int cnt = values[0] % y;
    if(cnt == 0) cnt = y;
    for(int i = 1;i < n;i++) {
        if(values[i] - values[i - 1] == 1) {
            cnt++;
        }else if(values[i] - values[i - 1] == -1) {
            cnt--;
        }
        if(cnt > y) {
            flag = false;
            break;
        }
    }
    if(flag) {
        cout << "YES" << endl;
        cout << MAX_VALUE << " " << y << endl;
    }else {
        cout << "NO" << endl;
    }
   return 0;
}

