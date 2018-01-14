#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int maxValue = -INF,maxValueCount = 1,minValue = INF,minValueCount = 1;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue > maxValue) {
            if(maxValue != -INF && maxValue < minValue) {
                minValue = maxValue;
                minValueCount = maxValueCount;
            }
            maxValue = tmpValue;
            maxValueCount = 1;
        }else if(tmpValue == maxValue) {
            maxValueCount++;
        }else if(tmpValue < minValue) {
            minValue = tmpValue;
            minValueCount = 1;
        }else if(tmpValue == minValue) {
            minValueCount++;
        }
    }
    if(minValue == INF) {
        long long result = (1 + maxValueCount - 1) * 1LL * (maxValueCount - 1) / 2;
        cout << 0 << " " << result << endl;
    }else {
        cout << maxValue - minValue << " " << maxValueCount * 1LL * minValueCount << endl;
    }
    return 0;
}
