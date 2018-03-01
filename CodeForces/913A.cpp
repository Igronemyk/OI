#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int countTwoValue(int value) {
    int countResult = 0;
    long long calValue = 1;
    while(calValue < value) {
        calValue *= 2;
        countResult++;
    }
    return countResult;
}

int quickPow(int a,int b) {
    int result = 1,base = a;
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
    int n,m;
    cin >> n >> m;
    int countTwo = countTwoValue(m);
    if(countTwo < n) {
        cout << m << endl;
    }else {
        cout << m % quickPow(2,n) << endl;
    }
    return 0;
}
