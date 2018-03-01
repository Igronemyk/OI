#include <iostream>
#include <algorithm>
using namespace std;


double area(double x1,double y1,double x2,double y2,double x,double y) {
	return (x1*y2+x2*y+x*y1)-(x*y2+x1*y+x2*y1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    double x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int result = 0;
    for(int i = 2;i < n;i++) {
        double tmpX,tmpY;
        cin >> tmpX >> tmpY;
        if(area(x1,y1,x2,y2,tmpX,tmpY) >= 0.00) {
            result++;
        }
        x1 = x2;
        y1 = y2;
        x2 = tmpX;
        y2 = tmpY;
    }
    cout << result << endl;
    return 0;
}
