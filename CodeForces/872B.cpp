#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main(){
    ios::sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    int minValue = INF,maxValue = -INF;
    int *values = new int[n],*minValueCount = new int[n],*minValueCount2 = new int[n];
    fill(minValueCount2,minValueCount2 + n,INF);
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        minValue = min(minValue,tmpValue);
        maxValue = max(maxValue,tmpValue);
        values[i] = tmpValue;
        minValueCount[i] = minValue;
    }
    if(k == 1) {
        cout << minValue << endl;
    }else if(k == 2) {
        int tmpMinValue = INF;
        for(int i = n - 1;i >= 0;i--) {
            tmpMinValue = min(tmpMinValue,values[i]);
            minValueCount2[i] = tmpMinValue;
        }
        int result = -INF;
        for(int i = 0;i < n - 1;i++) {
            result = max(result,max(minValueCount[i],minValueCount2[i + 1]));
        }
        cout << result << endl;
    }else {
        cout << maxValue << endl;
    }
    return 0;
}

