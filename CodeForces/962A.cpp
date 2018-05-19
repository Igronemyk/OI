#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int *values = new int[n];
    long long sumValues = 0;
    for(int i = 0;i < n;i++) {
        cin >> values[i];
        sumValues += values[i];
    }
    long long nowValues = 0;
    for(int i = 0;i < n;i++) {
        nowValues += values[i];
        if(nowValues * 2 >= sumValues) {
            cout << i + 1 << endl;
            break;
        }
    }
    return 0;
}
