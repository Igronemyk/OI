#include <iostream>

using namespace std;

const int MODDER = 1e9 + 7;

long long quickPow(int a,int b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result = (result * base) % MODDER;
        base = (base * base) % MODDER;
        b >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int x,y;
    cin >> x >> y;
    if(y % x != 0) {
        cout << 0 << endl;
        return 0;
    }
    int value = y / x;
    if(value == 1) {
        cout << 1 << endl;
    }else if(value == 2) {
        cout << 1 << endl;
    }else {
        int val = value - 3;
        long long result = (3 * quickPow(2,val)) % MODDER;
        cout << result << endl;
    }
    return 0;
}
