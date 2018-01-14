#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool isPreffix(string str1,string str2) {
    int length = str1.size();
    for(int i = 0;i < length;i++) {
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    map<string,vector<string> > values;
    for(int i = 0;i < n;i++) {
        string name;
        int numberCount;
        cin >> name >> numberCount;
        while(numberCount--) {
            string tmpValue;
            cin >> tmpValue;
            reverse(tmpValue.begin(),tmpValue.end());
            values[name].push_back(tmpValue);
        }
    }
    cout << values.size() << endl;
    vector<string> tmpResult;
    for(map<string,vector<string> >::iterator it = values.begin();it != values.end();it++) {
        sort(it->second.begin(),it->second.end());
        tmpResult.clear();
        cout << it->first << " ";
        for(vector<string>::iterator it1 = it->second.begin();it1 != it->second.end();it1++) {
            vector<string>::iterator nextIt = it1 + 1;
            string tmpValue = *it1;
            reverse(tmpValue.begin(),tmpValue.end());
            if(nextIt == it->second.end()) {
                tmpResult.push_back(tmpValue);
                continue;
            }
            if(!isPreffix(*it1,*nextIt)) {
                tmpResult.push_back(tmpValue);
            }
        }
        cout << tmpResult.size() << " ";
        for(vector<string>::iterator it1 = tmpResult.begin();it1 != tmpResult.end();it1++) {
            cout << *it1 << " ";
        }
        cout << endl;
    }
    return 0;
}
