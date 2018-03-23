#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long n,q;
    cin >> n >> q;
    while(q--) {
        long long pos;
        cin >> pos;
        if(pos & 1) {
            cout << (pos / 2) + 1 << endl;
        }else {
            long long x = n - 1 - pos / 2 + 1;// the x-th space
            while(!(pos & 1)) {
                pos += x;
                if(!(pos & 1)) {
                    x = n - 1 - pos / 2 + 1;
                }
            }
            cout << (pos / 2) + 1 << endl;
        }
    }
    return 0;
}
