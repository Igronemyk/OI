#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    bool reCounted = false;
    int result = 0,lastValue = -1,firstValue = -1;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(lastValue == -1) {
            lastValue = tmpValue;
            firstValue = tmpValue;
            continue;
        }
        if(!reCounted) {
            if(tmpValue < lastValue) {
                if(tmpValue <= firstValue) {
                    reCounted = true;
                    result++;
                }else {
                    result = -1;
                    break;
                }
            }
        }else {
            if(tmpValue < lastValue || tmpValue > firstValue) {
                result = -1;
                break;
            }else {
                result++;
            }
        }
        lastValue = tmpValue;
    }
    cout << result << endl;
    return 0;
}
