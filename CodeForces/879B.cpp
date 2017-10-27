#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    long long k;
    cin >> n >> k;
    if(2 * n + 20 >= k) {
        deque<int> val;
        for(int i = 0;i < n;i++) {
            int tmpValue;
            cin >> tmpValue;
            val.push_back(tmpValue);
        }
        int *countWin = new int[n + 1],result = -1;
        memset(countWin,0,sizeof(int) * (n + 1));
        while(true) {
            int first = val.front();
            val.pop_front();
            int second = val.front();
            val.pop_front();
            if(second > first) {
                countWin[second]++;
                if(countWin[second] == k) {
                    result = second;
                    break;
                }
                val.push_front(second);
                val.push_back(first);
            }else {
                countWin[first]++;
                if(countWin[first] == k) {
                    result = first;
                    break;
                }
                val.push_front(first);
                val.push_back(second);
            }
        }
        cout << result << endl;
    }else {
        int maxValue = 0;
        for(int i = 0;i < n;i++) {
            int tmpValue;
            cin >> tmpValue;
            maxValue = max(maxValue,tmpValue);
        }
        cout << maxValue << endl;
    }
    return 0;
}

