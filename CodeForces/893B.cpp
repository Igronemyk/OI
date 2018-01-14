#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    for(int i = N;i > 0;i--) {
        if(N % i != 0) continue;
        bool status = 0;
        int zeroCount = 0,oneCount = 0;
        int tmpValue = i;
        bool flag = true;
        while(tmpValue) {
            if(tmpValue & 1) {
                if(!status) {
                    status = true;
                }
                oneCount++;
            }else {
                if(status) {
                    flag = false;
                    break;
                }else {
                    zeroCount++;
                }
            }
            tmpValue >>= 1;
        }
        if(!flag) continue;
        if(zeroCount + 1 == oneCount) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
