#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        cin >> values[i];
        values[i]--;
    }
    for(int i = 0;i < n;i++) {
        int tmpValue = i;
        tmpValue = values[tmpValue];
        tmpValue = values[tmpValue];
        tmpValue = values[tmpValue];
        if(tmpValue == i) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
