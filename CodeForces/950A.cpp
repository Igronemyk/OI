#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int l,r,a;
    cin >> l >> r >> a;
    if(l > r) {
        swap(l,r);
    }
    if(r - l >= a) {
        l += a;
        cout << min(l,r) * 2 << endl;
    }else {
        cout << (r + (a - (r - l)) / 2) * 2 << endl;
    }
    return 0;
}
