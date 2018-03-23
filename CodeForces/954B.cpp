#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;
    for(int i = n / 2;i >= 1;i--) {
        if(s.substr(0,i) == s.substr(i,i)) {
            cnt = i;
            break;
        }
    }
    if(cnt == 0) {
        cout << n << endl;
    }else {
        cout << n - cnt + 1 << endl;
    }
    return 0;
}

