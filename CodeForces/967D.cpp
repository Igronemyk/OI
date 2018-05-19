#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <iostream>
#include <cstddef>
#include <iomanip>

using namespace std;

const int MAXN = 300010;

pair<int,int> initValues[MAXN];

int signs[MAXN],weights[MAXN],rightPos[MAXN],preMin[MAXN],sufMin[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,x1,x2;
    cin >> n >> x1 >> x2;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        initValues[i] = make_pair(tmpValue,i + 1);
    }
    sort(initValues,initValues + n);
    for(int i = 0;i < n;i++) {
        weights[i] = initValues[i].first;
        signs[i] = initValues[i].second;
        int length = (x2 + weights[i] - 1) / weights[i];
        rightPos[i] = i + length - 1;
        sufMin[i] = rightPos[i];
        preMin[i] = rightPos[i];
    }
    for(int i = 1;i < n;i++) {
        preMin[i] = min(preMin[i],preMin[i - 1]);
    }
    for(int i = n - 2;i >= 0;i--) {
        sufMin[i] = min(sufMin[i],sufMin[i + 1]);
    }
    for(int i = 0;i < n;i++) {
        int length = (x1 + weights[i] - 1) / weights[i],start = i + length;
        if(start > n) continue;
        if(i > 0) {
            int nowMinValue = preMin[i - 1],leftCnt = n - length;
            if(nowMinValue < leftCnt) {
                int selectPos = -1;
                for(int j = 0;j < i;j++) {
                    if(rightPos[j] == nowMinValue) {
                        selectPos = j;
                        break;
                    }
                }
                if(selectPos == -1) continue;
                cout << "Yes" << endl;
                int usedCnt = (x2 + weights[selectPos] - 1) / weights[selectPos];
                cout << length << " " << usedCnt << endl;
                for(int j = i;j < start;j++) {
                    cout << signs[j] << " ";
                }
                cout << endl;
                int now = selectPos;
                while(now < i && usedCnt > 0) {
                    cout << signs[now] << " ";
                    now++;
                    usedCnt--;
                }
                if(usedCnt > 0) {
                    now = start;
                    while(usedCnt--) {
                        cout << signs[now] << " ";
                        now++;
                    }
                }
                cout << endl;
                return 0;
            }
        }
        if(start < n) {
            int nowMinValue = sufMin[start];
            if(nowMinValue < n) {
                int selectPos = -1;
                for(int j = start;j < n;j++) {
                    if(rightPos[j] == nowMinValue) {
                        selectPos = j;
                        break;
                    }
                }
                if(selectPos == -1) continue;
                cout << "Yes" << endl;
                int usedCnt = (x2 + weights[selectPos] - 1) / weights[selectPos];
                cout << length << " " << usedCnt << endl;
                for(int j = i;j < start;j++) {
                    cout << signs[j] << " ";
                }
                cout << endl;
                int now = selectPos;
                while(usedCnt--) {
                    cout << signs[now] << " ";
                    now++;
                }
                cout << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}
