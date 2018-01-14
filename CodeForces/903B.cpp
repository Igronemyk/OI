#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int vH,vA,vC,mH,mA;
    cin >> vH >> vA >> vC >> mH >> mA;
    queue<int> values;
    int countRound = 0;
    while(mH) {
        countRound++;
        if(mH <= vA) {
            mH = 0;
            values.push(0);
            continue;
        }
        if(vH <= mA) {
            vH += vC;
            vH -= mA;
            values.push(1);
            continue;
        }
        mH -= vA;
        vH -= mA;
        values.push(0);
    }
    cout << countRound << endl;
    while(!values.empty()) {
        int tmpValue = values.front();
        values.pop();
        if(tmpValue == 1) {
            cout << "HEAL" << endl;
        }else {
            cout << "STRIKE" << endl;
        }
    }
    return 0;
}
