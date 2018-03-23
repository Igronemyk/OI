#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    vector<int> values1;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        values1.push_back(tmpValue);
    }
    int nowPos = 0,nowFirstSum = 0,nowSecondSum = 0,result = 0;
    for(int i = 0;i < m;i++) {
        int tmpValue;
        cin >> tmpValue;
        nowSecondSum += tmpValue;
        while(nowSecondSum > nowFirstSum) {
            nowFirstSum += values1[nowPos++];
        }
        if(nowSecondSum == nowFirstSum) {
            result++;
            nowFirstSum = 0;
            nowSecondSum = 0;
        }
    }
    cout << result << endl;
    return 0;
}
