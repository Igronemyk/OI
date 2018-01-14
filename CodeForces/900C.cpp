#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    priority_queue<int> que;
    int n;
    cin >> n;
    int *countValue = new int[n + 1];
    int *status = new int[n + 1];
    fill(countValue,countValue + n + 1,0);
    que.push(0);
    {
        int tmpValue;
        cin >> tmpValue;
        status[tmpValue] = -1;
        que.push(tmpValue);
    }
    for(int i = 0;i < n - 1;i++) {
        int tmpValue;
        cin >> tmpValue;
        if(tmpValue > que.top()) {
            status[tmpValue] = -1;
            que.push(tmpValue);
            continue;
        }else {
            int tmpTop = que.top();
            que.pop();
            if(tmpValue > que.top()) {
                countValue[tmpTop]++;
                status[tmpValue] = tmpTop;
            }else {
                status[tmpValue] = -2;
            }
            que.push(tmpTop);
            que.push(tmpValue);
        }
    }
    int maxPos = 1;
    for(int i = 2;i <= n;i++) {
        if(countValue[i] > countValue[maxPos]) {
            maxPos = i;
        }
    }
    if(status[maxPos] == -1 && countValue[maxPos] <= 1) {
        int minValue = -1;
        for(int i = 1;i <= n;i++) {
            if(i < maxPos) {
                if(status[i] != -1) {
                    minValue = i;
                    break;
                }
            }else {
                if(status[i] == -2) {
                    minValue = i;
                    break;
                }
            }
        }
        cout << (minValue == -1 ? maxPos : minValue) << endl;
    }else {
        cout << maxPos << endl;
    }
    return 0;
}
