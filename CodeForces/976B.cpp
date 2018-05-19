#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long n,m,k;
    cin >> n >> m >> k;
    if(n * m - 1 == k) {
        cout << "1 2" << endl;
        return 0;
    }
    if(k < n) {
        cout << k + 1 << " 1" << endl;
        return 0;
    }
    k -= n;
    int value1 = k / (m - 1),value2 = k % (m - 1);
    if(value1 & 1) {
        cout << n - value1 << " " << m - value2 << endl;
    }else {
        cout << n - value1 << " " << value2 + 2 << endl;
    }
    return 0;
}

