#include <iostream>
#include <algorithm>

using namespace std;

int getValue(int n) {
    int i;
    int countTimes = 0;
    for(i = 2;i <= n;i++) {
        while(n % i == 0) {
            countTimes++;
            n /= i;
            if(countTimes == 2) return n;
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--) {
        int n;
        cin >> n;
        int tmpResult = getValue(n);
        if(tmpResult != -1) {
            cout << tmpResult << endl;
            continue;
        }else{
            int value = n / 2;
            int value2 = n - value;
            while(value <= n && (getValue(value) == -1 || getValue(value2) == -1)) {
                value++;
                value2--;
            }
            if(value == n + 1) {
                cout << -1 << endl;
            }else {
                cout << getValue(value) + getValue(value2) << endl;
            }
        }
    }
    return 0;
}
