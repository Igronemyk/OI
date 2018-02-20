#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N,A,B;
    cin >> N >> A >> B;
    int useA = -1,useB = -1;
    for(int i = 0;;i++) {
        int tmpValue = N - i * A;
        if(tmpValue < 0) break;
        if(tmpValue % B == 0) {
            useA = i;
            useB = tmpValue / B;
            break;
        }
    }
    if(useA == -1 && useB == -1) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> result;
    int nowPos = 1;
    while(useA--) {
        int startPos = nowPos,endPos = nowPos + A - 1;
        for(int i = startPos;i < endPos;i++) {
            cout << i + 1 << " ";
            result.push_back(i + 1);
        }
        cout << startPos << " ";
        nowPos = endPos + 1;
    }
    while(useB--) {
        int startPos = nowPos,endPos = nowPos + B - 1;
        for(int i = startPos;i < endPos;i++) {
            cout << i + 1 << " ";
            result.push_back(i + 1);
        }
        cout << startPos << " ";
        nowPos = endPos + 1;
    }
    cout << endl;
    return 0;
}

