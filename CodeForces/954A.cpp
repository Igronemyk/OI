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
    int cnt = static_cast<int>(s.size());
    char lastChar = s[0];
    for(string::iterator it = s.begin() + 1;it != s.end();it++) {
        if(lastChar != 0 && *it != lastChar) {
            cnt--;
            lastChar = 0;
        }else {
            lastChar = *it;
        }
    }
    cout << cnt << endl;
    return 0;
}
