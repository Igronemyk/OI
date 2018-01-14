#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b >> c;
    int result = -1;
    for(int i = 1;i <= 1000000;i++) {
        a *= 10;
        int splitValue = a / b;
        if(splitValue == c) {
            result = i;
            break;
        }
        a -= splitValue * b;
    }
    cout << result << endl;
    return 0;
}
