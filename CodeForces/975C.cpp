#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,q;
    cin >> n >> q;
    long long sumValue = 0;
    vector<long long> values;
    for(int i = 0;i < n;i++) {
        long long tmpValue;
        cin >> tmpValue;
        sumValue += tmpValue;
        values.push_back(sumValue);
    }
    long long nowValue = 0;
    for(int i = 0;i < q;i++) {
        long long tmpValue;
        cin >> tmpValue;
        nowValue += tmpValue;
        vector<long long>::iterator it = upper_bound(values.begin(),values.end(),nowValue);
        int cnt = values.end() - it;
        if(cnt == 0) {
            cout << n << endl;
            nowValue = 0;
        }else {
            cout << cnt << endl;
        }
    }
    return 0;
}

