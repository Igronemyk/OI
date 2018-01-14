#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int diffX = x2 - x1,diffY = y2 - y1;
    if(diffX == 0) {
        cout << x1 + diffY << " " << y1 << " " << x1 + diffY << " " << y2 << endl;
    }else if(diffY == 0){
        cout << x1 << " " << y1 + diffX << " " << x2 << " " << y1 + diffX << endl;
    }else if(abs(diffX) == abs(diffY)) {
        cout << x1 << " " << y1 + diffY << " " << x1 + diffX << " " << y1 << endl;
    }else {
        cout << -1 << endl;
    }
    return 0;
}
