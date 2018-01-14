#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int value = n % 10,tmpValue = n / 10 * 10;
    if(value <= 5) {
        cout << tmpValue << endl;
    }else {
        cout << tmpValue + 10 << endl;
    }
    return 0;
}
