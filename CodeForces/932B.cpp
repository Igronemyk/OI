#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_VAL_RANGE = 1e6;

vector<int> values[MAX_VAL_RANGE + 1];

int g[MAX_VAL_RANGE + 1];

int getF(int value) {
    int result = 1;
    while(value) {
        int tmp = value % 10;
        value /= 10;
        if(tmp == 0) continue;
        result *= tmp;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for(int i = 0;i < 10;i++) {
        g[i] = i;
        values[i].push_back(i);
    }
    for(int i = 10;i <= MAX_VAL_RANGE;i++) {
        g[i] = g[getF(i)];
        values[g[i]].push_back(i);
    }
    int Q;
    cin >> Q;
    while(Q--) {
        int l,r,k;
        cin >> l >> r >> k;
        vector<int>::iterator start = lower_bound(values[k].begin(),values[k].end(),l),end = upper_bound(values[k].begin(),values[k].end(),r);
        cout << end - start << endl;
    }
    return 0;
}
