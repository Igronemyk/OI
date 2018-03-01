#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

bool isWin(int m,int k) {
    if(m == 1) {
        return false;
    }
    if(k == 1) {
        return true;
    }
    set<int> values;
    int top = static_cast<int>(sqrt(m));
    for(int i = 2;i <= top;i++) {
        if(m % i == 0) {
            values.insert(i);
            values.insert(m / i);
        }
    }
    set<int>::iterator it = values.lower_bound(k);
    return it != values.end();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    if(!(n & 1)) {
        cout << "Marsel" << endl;
    }else if(isWin(m,k)) {
        cout << "Timur" << endl;
    }else {
        cout << "Marsel" << endl;
    }
    return 0;
}
