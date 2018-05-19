#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstddef>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    string s;
    cin >> s;
    if(s == "0") {
        cout << s << endl;
        return 0;
    }
    int cntOne = 0,cntZero = 0;
    for(string::iterator it = s.begin();it != s.end();it++) {
        if(*it == '1') {
            cntOne++;
        }else {
            cntZero++;
        }
    }
    cout << "1";
    while(cntZero--) {
        cout << "0";
    }
    cout << endl;
    return 0;
}
