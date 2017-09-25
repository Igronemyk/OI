#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string s;
    cin >> s;
    string s1 = s;
    int ignoreStart = 0,ignoreEnd = 0;
    for(string::iterator it = s.begin();it != s.end();it++){
        if(*it == '0') ignoreStart++; else break;
    }
    for(int i = s1.size() - 1;i >= 0;i--){
        if(s[i] == '0') ignoreEnd++; else break;
    }
    s = s.substr(ignoreStart,s.size() - ignoreStart - ignoreEnd);
    reverse(s1.begin(),s1.end());
    s1 = s1.substr(ignoreEnd,s1.size() - ignoreEnd - ignoreStart);
    cout << ((s == s1) ? "YES" : "NO") << endl;
    return 0;
}
