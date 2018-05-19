#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,a,b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int prevValue = -1,result = 0;
    for(string::iterator it = s.begin();it != s.end();it++) {
        char nowChar = *it;
        if(nowChar == '.') {
            if(prevValue == -1) {
                if(a < b) {
                    prevValue = 1;
                    result++;
                    b--;
                }else {
                    prevValue = 0;
                    result++;
                    a--;
                }
            }else if(prevValue == 0) {
                if(b == 0) {
                    prevValue = -1;
                }else {
                    prevValue = 1;
                    result++;
                    b--;
                }
            }else if(prevValue == 1) {
                if(a == 0) {
                    prevValue = -1;
                }else {
                    prevValue = 0;
                    result++;
                    a--;
                }
            }
            if(a + b == 0) {
                break;
            }
        }else {
            prevValue = -1;
        }
    }
    cout << result << endl;
    return 0;
}

