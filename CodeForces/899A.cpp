#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int twoCount = 0,oneCount = 0;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue == 1) {
            oneCount++;
        }else {
            twoCount++;
        }
    }
    if(twoCount >= oneCount) {
        cout << oneCount << endl;
    }else {
        cout << twoCount + (oneCount - twoCount) / 3 << endl;
    }
    return 0;
}
