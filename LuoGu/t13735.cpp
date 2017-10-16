#include <iostream>
#include <string>

using namespace std;

struct Data{
    char value;
    int countTimes;
    bool canBeMore;
    Data() : value(' '),countTimes(0),canBeMore(false) {}
};

Data charInS[30010],charInT[30010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--) {
        string s,t;
        cin >> s >> t;
        int sizeS = static_cast<int>(s.size()),sizeT = static_cast<int>(t.size());
        int posS = 0,posT = 0;
        char prevChar = ' ';
        for(string::iterator it = s.begin();it != s.end();it++) {
            if(*it == '*') {
                if(posS == 0) continue;
                charInS[posS - 1].canBeMore = true;
                continue;
            }
            if(prevChar == *it) {
                charInS[posS - 1].countTimes++;
                continue;
            }
            charInS[posS++].value = *it;
            prevChar = *it;
        }
        prevChar = ' ';
        for(string::iterator it = t.begin();it != t.end();it++) {
            if(prevChar == *it) {
                charInT[posT - 1].countTimes++;
                continue;
            }
            charInT[posT++].value = *it;
            prevChar = *it;
        }
        if(posS != posT) {
            cout << "No" << endl;
        }else {
            bool flag = true;
            for(int i = 0;i < posS;i++) {
                if(charInS[i].value != charInT[i].value) {
                    flag = false;
                    break;
                }
                if(charInS[i].countTimes > charInT[i].countTimes) {
                    flag = false;
                    break;
                }
                if(charInS[i].countTimes < charInT[i].countTimes && !charInS[i].canBeMore) {
                    flag = false;
                    break;
                }
            }
            cout << (flag ? "Yes" : "No") << endl;
        }
        for(int i = 0;i < posS;i++) {
            charInS[i].countTimes = 0;
            charInS[i].canBeMore = false;
        }
        for(int i = 0;i < posT;i++) {
            charInT[i].countTimes = 0;
        }
    }
    return 0;
}

