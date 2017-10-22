#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    map<char,int> charMap;
    cin >> s;
    for(string::iterator it = s.begin();it != s.end();it++) {
        charMap[*it]++;
    }
    int countWrongNum = 0;
    vector<char> wrongs;
    for(map<char,int>::iterator it = charMap.begin();it != charMap.end();it++) {
        if(it->second % 2 != 0) {
            countWrongNum++;
            wrongs.push_back(it->first);
            it->second--;
        }
    }
    if(countWrongNum == 0) {
        cout << 1 << endl;
        map<char,int>::iterator it = charMap.begin();
        vector<char> selectChar;
        while(it != charMap.end()) {
            selectChar.push_back(it->first);
            it->second -= 2;
            if(it->second == 0) it++;
        }
        for(vector<char>::iterator it = selectChar.begin();it != selectChar.end();it++) {
                cout << *it;
        }
        for(vector<char>::reverse_iterator it = selectChar.rbegin();it != selectChar.rend();it++) {
                cout << *it;
        }
        cout << endl;
    }else if(n % countWrongNum == 0 && (n / countWrongNum) % 2 != 0) {
        cout << countWrongNum << endl;
        int len = n / countWrongNum / 2;
        map<char,int>::iterator it = charMap.begin();
        for(int i = 0;i < countWrongNum;i++) {
            vector<char> selectChar;
            for(int j = 0;j < len;j++) {
                selectChar.push_back(it->first);
                it->second -= 2;
                if(it->second == 0) it++;
            }
            for(vector<char>::iterator it = selectChar.begin();it != selectChar.end();it++) {
                cout << *it;
            }
            cout << wrongs[i];
            for(vector<char>::reverse_iterator it = selectChar.rbegin();it != selectChar.rend();it++) {
                cout << *it;
            }
            cout << " ";
        }
        cout << endl;
    }else {
        cout << n << endl;
        map<char,int>::iterator it = charMap.begin();
        while(it != charMap.end()) {
            cout << it->first << " ";
            it->second--;
            if(it->second == 0) it++;
        }
        cout << endl;
    }
    return 0;
}
