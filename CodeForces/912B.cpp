#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

long long quickPow(int a,int b) {
    long long result = 1,base = a;
    while(b) {
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long n,k;
    cin >> n >> k;
    long long tmpValue = n;
    int logTwoCount = 0;
    while(tmpValue) {
        logTwoCount++;
        tmpValue >>= 1;
    }
    if(k == 1) {
        cout << n << endl;
    }else {
        cout << quickPow(2,logTwoCount) - 1 << endl;
    }
    return 0;
}

