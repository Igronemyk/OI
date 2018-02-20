#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string str;
    cin >> str;
    cout << str;
    reverse(str.begin(),str.end());
    cout << str <<endl;
    return 0;
}
