#include <iostream>
#include <algorithm>

using namespace std;

int values[17] = {-1,-1,-1,-1,1,-1,1,-1,2,1,2,-1,3,2,3,2,4};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    while(q--) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue <= 16) {
            cout << values[tmpValue] << endl;
        }else {
            if(tmpValue % 4 == 0) {
                cout << tmpValue / 4 << endl;
            }else {
                int divValue = tmpValue / 4,modValue = tmpValue % 4;
                divValue -= 3;
                int nowValue = 12 + modValue;
                if(values[nowValue] == -1) {
                    cout << -1 << endl;
                }else {
                    cout << values[nowValue] + divValue << endl;
                }
            }
        }
    }
    return 0;
}
