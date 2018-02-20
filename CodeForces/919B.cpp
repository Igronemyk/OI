#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> k;
    int value = 1;
    while(true) {
        int tmpValue = value,sum = 0;
        while(tmpValue) {
            sum += tmpValue % 10;
            tmpValue /= 10;
        }
        if(sum == 10) {
            k--;
        }
        if(k == 0) {
            printf("%d\n",value);
            break;
        }
        value++;
    }
    return 0;
}
