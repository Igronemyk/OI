#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

const int MAX_CNT = 19;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string a,b;
    cin >> a >> b;
    int *cntA = new int[MAX_CNT],*cntB = new int[MAX_CNT];
    int posA = 0,posB = 0;
    for(string::reverse_iterator it = a.rbegin();it != a.rend();it++) {
        cntA[posA++] = *it - '0';
    }
    for(string::reverse_iterator it = b.rbegin();it != b.rend();it++) {
        cntB[posB++] = *it - '0';
    }
    if(posB > posA) {
        sort(cntA,cntA + posA);
        for(int i = posA - 1;i >= 0;i--) {
            cout << cntA[i];
        }
        cout << endl;
        return 0;
    }
    map<int,int> values,saveValues;
    for(int i = 0;i < posA;i++) {
        values[cntA[i]]++;
        saveValues[cntA[i]]++;
    }
    int acceptSamePos = posB;
    for(int nowPos = posB - 1;nowPos >= 0;nowPos--) {
        map<int,int>::iterator it = values.lower_bound(cntB[nowPos]);
        if(it == values.end() || it->first > cntB[nowPos]) {
            break;
        }
        it->second--;
        if(it->second == 0) values.erase(it);
        if(nowPos != 0) {
            map<int,int>::iterator it = values.lower_bound(cntB[nowPos - 1]);
            if(it != values.begin()) {
                acceptSamePos = nowPos;
            }else if(it == values.end() || it->first > cntB[nowPos - 1]) {
                break;
            }
        }else {
            acceptSamePos = nowPos;
        }
    }
    for(int i = posB - 1;i >= acceptSamePos;i--) {
        cout << cntB[i];
        saveValues[cntB[i]]--;
        if(saveValues[cntB[i]] == 0) saveValues.erase(cntB[i]);
    }
    if(acceptSamePos != 0) {
        acceptSamePos--;
        map<int,int>::iterator it = saveValues.lower_bound(cntB[acceptSamePos]);
        it--;
        cout << it->first;
        it->second--;
        if(it->second == 0) saveValues.erase(it);
    }
    for(map<int,int>::reverse_iterator it = saveValues.rbegin();it != saveValues.rend();it++) {
        while(it->second) {
            cout << it->first;
            it->second--;
        }
    }
    cout << endl;
    return 0;
}

