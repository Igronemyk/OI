#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,pos,l,r;
    cin >> n >> pos >> l >> r;
    if(l == 1) {
        if(r == n) {
            cout << 0 << endl;
        }else {
            cout << abs(r - pos) + 1 << endl;
        }
        return 0;
    }
    if(r == n) {
        if(l == 1) {
            cout << 0 << endl;
        }else {
            cout << abs(l - pos) + 1 << endl;
        }
        return 0;
    }
    int leftDis = abs(l - pos);
    int rightDis = abs(r - pos);
    int length = r - l;
    int minDis = min(leftDis,rightDis);
    cout << minDis + length + 2 << endl;
    return 0;
}

