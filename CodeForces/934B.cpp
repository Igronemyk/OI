#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> k;
    int useEight = k / 2;
    if(useEight > 18 || (useEight == 18 && k % 2 != 0)) {
        cout << -1 << endl;
        return 0;
    }
    for(int i = 0;i < useEight;i++) {
        cout << 8;
    }
    if(k % 2 != 0) {
        cout << 6;
    }
    cout << endl;
    return 0;
}

