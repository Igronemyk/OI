#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int countLeft = 0,countRight = 0;
    for(int i = 0;i < n;i++) {
        int x,y;
        cin >> x >> y;
        if(x > 0) {
            countRight++;
        }else {
            countLeft++;
        }
    }
    if(countRight == 1 || countLeft == 1 || countRight == 0 || countLeft == 0) {
        cout << "Yes" << endl;
    }else {
        cout << "No" << endl;
    }
    return 0;
}
