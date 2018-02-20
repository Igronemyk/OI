#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

int powTwo(int value) {
    return value * value;
}

int getDis(int x1,int y1,int x2,int y2) {
    return powTwo(x1 - x2) + powTwo(y1 - y2);
}

int main() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << 2 << endl;
        return 0;
    }else if(n == 2) {
        int x1,y1,r1,x2,y2,r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        int criDis = getDis(x1,y1,x2,y2);
    }
    return 0;
}
