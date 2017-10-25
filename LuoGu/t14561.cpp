#include <iostream>
#include <string>

using namespace std;

char toLowerCase(char c) {
    if(c >= 'a' && c <= 'z') return c;
    return c - 'A' + 'a';
}

char toUpperCase(char c) {
    if(c >= 'A' && c <= 'Z') return c;
    return c - 'a' + 'A';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    getline(cin,s);
    bool isWord = false;
    for(string::iterator it = s.begin();it != s.end();it++) {
        char tmpChar = *it;
        if(tmpChar == '.') {
            cout << tmpChar;
            if(isWord) isWord = false;
            continue;
        }else if(tmpChar == ' ') {
            cout << tmpChar;
            continue;
        }
        if(!isWord) {
            cout << toUpperCase(tmpChar);
            isWord = true;
        }else {
            cout << toLowerCase(tmpChar);
        }
    }
    return 0;
}
