#include <iostream>
#include <string>

using namespace std;

bool check(char c){
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(){
    string s;
    cin >> s;
    bool isStart = false,isSame = true;char lastChar;int countLength = 0;
    for(string::iterator it = s.begin();it != s.end();it++){
        if(!isStart){
            if(!check(*it)){
                isStart = true;
                isSame = true;
                countLength = 1;
                lastChar = *it;
            }
            cout << *it;
            continue;
        }
        if(check(*it)){
            isStart = false;
        }else{
            if(*it != lastChar){
                isSame = false;
                lastChar = *it;
            }
            countLength++;
            if(countLength >= 3 && !isSame){
                cout << " ";
                countLength = 1;
                isSame = true;
            }
        }
        cout << *it;
    }
    cout << endl;
    return 0;
}
