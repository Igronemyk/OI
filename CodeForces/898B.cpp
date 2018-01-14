#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,a,b;
    cin >> n >> a >> b;
    int valueA = 0,resultA = -1,resultB = -1;
    bool found = false;
    while(true) {
        int leftValue = n - valueA * a;
        if(leftValue % b == 0) {
            found = true;
            resultA = valueA;
            resultB = leftValue / b;
            break;
        }
        valueA++;
        if(valueA * a > n) break;
    }
    if(found) {
        cout << "YES" << endl;
        cout << resultA << " " << resultB << endl;
    }else {
        cout << "NO" << endl;
    }
    return 0;
}

