#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int limit = n / 2;
    for(int i = 0;i < n;i++) {
        int nowMaxDisplayDis = limit - abs(limit - i);
        for(int j = 0;j < n;j++) {
            if(abs(limit - j) <= nowMaxDisplayDis) {
                cout << "D";
            }else {
                cout << "*";
            }
        }
        cout << endl;
    }
    return 0;
}
