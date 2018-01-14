#include <iostream>
#include <string>

using namespace std;

int main() {
    int n,m;
    string s;
    cin >> n >> s >> m;
    int result = 0,tmpResult = 0,tmpDo = 0;
    for(int i = 0;i < n;i++) {
        switch(s[i]) {
            case 'a': {
                if(tmpDo % 2 == 0) {
                    tmpDo++;
                }else {
                    tmpResult = 0;
                    tmpDo = 1;
                }
                break;
            }
            case 'b': {
                if(tmpDo % 2 == 0) {
                    tmpResult = 0;
                    tmpDo = 0;
                }else {
                    tmpDo++;
                }
                break;
            }
            case '?': {
                tmpDo++;
                tmpResult++;
                break;
            }
        }
        if(tmpDo == m) {
            tmpDo = 0;
            result += tmpResult;
            tmpResult = 0;
        }
    }
    cout << result << endl;
    return 0;
}
