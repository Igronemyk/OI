#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    map<double,int> cntValues;
    long double sumValue = 0,result = 0;
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) {
        long double tmpValue;
        cin >> tmpValue;
        cntValues[tmpValue]++;
        sumValue += tmpValue;
        int countNum = (i + 1) - cntValues[tmpValue - 1] - cntValues[tmpValue + 1];
        result += tmpValue * countNum - (sumValue - cntValues[tmpValue - 1] * (tmpValue - 1) - cntValues[tmpValue + 1] * (tmpValue + 1));
    }
    cout << fixed << setprecision(0) << result << endl;
    return 0;
}
