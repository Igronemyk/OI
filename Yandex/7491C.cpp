#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MODDER = 1e9 + 7;

int quickPow(int a,int b) {
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
    cout.tie(0);
    int n;
    cin >> n;
    int powValue = (n - 1) * (n - 1);
    cout << quickPow(n,powValue) << endl;
    return 0;
}
