#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

string data = "#31#29#31#30#31#30#31#31#30#31#30#31#31#28#31#30#31#30#31#31#30#31#30#31#31#28#31#30#31#30#31#31#30#31#30#31#31#28#31#30#31#30#31#31#30#31#30#31#31#29#31#30#31#30#31#31#30#31#30#31#31#28#31#30#31#30#31#31#30#31#30#31#";
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    stringstream ss;
    ss << '#';
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        ss << tmpValue;
        ss << '#';
    }
    string value;
    ss >> value;
    if(data.find(value) != -1) {
        cout << "YES" << endl;
    }else {
        cout << "NO" << endl;
    }
    return 0;
}

