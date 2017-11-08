#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int len = static_cast<int>(s.size());
    int zeroCount = 0;
    for(int i = len - 1;i >= 0;i--) {
        if(s[i] == '1' && zeroCount >= 6) {
            cout << "yes" << endl;
            return 0;
        }
        if(s[i] == '0') {
            zeroCount++;
        }
    }
    cout << "no" << endl;
    return 0;
}
