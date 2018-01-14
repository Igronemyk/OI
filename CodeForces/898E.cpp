#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int countNotSquare = 0,countSquare = 0;
    vector<long long> results,reResults;
    for(int i = 0;i < n;i++) {
        long long tmpValue;
        cin >> tmpValue;
        long double sqrtValue = sqrt(tmpValue);
        if(sqrtValue == floor(sqrtValue)) {
            countSquare++;
            if(tmpValue == 0) reResults.push_back(2); else reResults.push_back(1);
        }else {
            countNotSquare++;
            long long shouldValue1 = ceil(sqrtValue);
            shouldValue1 *= shouldValue1;
            long long shouldValue2 = floor(sqrtValue);
            shouldValue2 *= shouldValue2;
            results.push_back(min(shouldValue1 - tmpValue,tmpValue - shouldValue2));
        }
    }
    sort(results.begin(),results.end());
    sort(reResults.begin(),reResults.end());
    if(countSquare > countNotSquare) {
        int needValue = countSquare - countNotSquare;
        needValue /= 2;
        long long result = 0,pos = 0;
        while(needValue--) {
            result += reResults[pos];
            pos++;
        }
        cout << result << endl;
    }else if(countSquare == countNotSquare) {
        cout << 0 << endl;
    }else {
        int needValue = countNotSquare - countSquare;
        needValue /= 2;
        long long result = 0,pos = 0;
        while(needValue--) {
            result += results[pos];
            pos++;
        }
        cout << result << endl;
    }
    return 0;
}
