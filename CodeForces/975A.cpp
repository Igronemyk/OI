#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>
#include <string>
#include <set>

using namespace std;

int getValue(const string &s) {
    int value = 0;
    for(string::const_iterator it = s.begin();it != s.end();it++) {
        value |= (1 << (*it - 'a'));
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    set<int> values;
    for(int i = 0;i < n;i++) {
        string s;
        cin >> s;
        values.insert(getValue(s));
    }
    cout << values.size() << endl;
    return 0;
}
