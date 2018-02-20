#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long N,K;
    cin >> N >> K;
    long long nowMinLeftValue = N,nowAccessSign = -1,*values = new long long[K + 1];
    for(int i = 1;i <= K;i++) {
        long long tmpValue;
        cin >> tmpValue;
        values[i] = tmpValue;
        if(tmpValue > N) continue;
        long long tmpLeftValue = N % tmpValue;
        if(tmpLeftValue < nowMinLeftValue) {
            nowMinLeftValue = tmpLeftValue;
            nowAccessSign = i;
        }
    }
    if(nowAccessSign == -1) {
        cout << 1 << " " << 0 << endl;
    }else {
        cout << nowAccessSign << " ";
        cout << N / values[nowAccessSign] << endl;
    }
    return 0;
}
