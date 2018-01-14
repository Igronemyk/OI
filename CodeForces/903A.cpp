#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    while(n--) {
        int value;
        cin >> value;
        bool flag = false;
        for(int i = 0;i < 100;i++) {
            for(int j = 0;j < 100;j++) {
                if(i * 3 + j * 7 == value) {
                    flag = true;
                    goto outside;
                }
            }
        }
        outside:
        if(flag) {
            cout << "YES" << endl;
        }else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
