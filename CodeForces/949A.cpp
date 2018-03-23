#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    if(s[0] == '1') {
        cout << -1 << endl;
        return 0;
    }
    int length = s.size();
    int *nextPos = new int[length];
    vector<vector<int> > values;
    vector<int> tmp;
    tmp.push_back(0);
    values.push_back(tmp);
    int nowPos = 0;
    bool flag = true;
    for(int i = 1;i < length;i++) {
        bool isOne = s[i] == '1';
        if(isOne) {
            if(nowPos < values.size()) {
                values[nowPos].push_back(i);
                nowPos++;
            }else {
                flag = false;
                break;
            }
        }else {
            if(nowPos != 0) {
                nowPos--;
                values[nowPos].push_back(i);
            }else {
                vector<int> newVec;
                newVec.push_back(i);
                values.push_back(newVec);
            }
        }
    }
    if(flag && nowPos == 0) {
        cout << values.size() << endl;
        for(vector<vector<int> >::iterator it = values.begin();it != values.end();it++) {
            cout << it->size() << " ";
            for(vector<int>::iterator it1 = it->begin();it1 != it->end();it1++) {
                cout << (*it1) + 1 << " ";
            }
            cout << endl;
        }
    }else {
        cout << -1 << endl;
    }
    return 0;
}
