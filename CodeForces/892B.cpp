#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int *values = new int[n];
    fill(values,values + n,0);
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        int endIndex = max(0,i - 1);
        int startIndex = max(0,endIndex - tmpValue + 1);
        values[startIndex]--;
        values[endIndex + 1]++;
    }
    int countResult = 0;
    long long countNowValue = 0;
    for(int i = 0;i < n;i++) {
        countNowValue += values[i];
        if(countNowValue == 0) {
            countResult++;
        }
    }
    cout << countResult << endl;
    return 0;
}
