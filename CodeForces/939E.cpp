#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const double EPS = 1e-12;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int Q;
    cin >> Q;
    vector<long long> sumValues;
    sumValues.push_back(0);
    long long nowMaxValue = -1;
    while(Q--) {
        int opt;
        cin >> opt;
        if(opt == 1) {
            long long tmpValue;
            cin >> tmpValue;
            nowMaxValue = max(nowMaxValue,tmpValue);
            sumValues.push_back(tmpValue + *(sumValues.rbegin()));
        }else {
            int left = 0,right = sumValues.size() - 2;
            double result = 0;
            while(left < right) {
                //cout << "Doing " << left << " " << right << endl;
                int rangeLength = (right - left) / 3;
                int mid1 = left + rangeLength,mid2 = right - rangeLength;
                //cout << "Mid " << mid1 << " " << mid2 << endl;
                double midValue1 = (sumValues[mid1] + nowMaxValue) * 1.00 / (mid1 + 1),midValue2 = (sumValues[mid2] + nowMaxValue) * 1.00 / (mid2 + 1);
                //cout << "MidValue " << midValue1 << " " << midValue2 << endl;
                double resultValue1 = nowMaxValue - midValue1,resultValue2 = nowMaxValue - midValue2;
                if(resultValue1 - resultValue2 > EPS) {
                    if(resultValue1 > result) {
                        result = resultValue1;
                    }
                    right = mid2 - 1;
                }else {
                    if(resultValue2 > result) {
                        result = resultValue2;
                    }
                    left = mid1 + 1;
                }
            }
            cout << fixed << setprecision(10) << result << endl;
        }

    }
    return 0;
}
