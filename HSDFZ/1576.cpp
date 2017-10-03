#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int value[10000];

int main(){
    int s,t,w;
    cin >> s >> t >> w;
    s--;t--;
    string str;
    cin >> str;
    for(string::iterator it = str.begin();it != str.end();it++){
        value[it - str.begin()] = *it - 'a';
    }
    int nowLength = w;
    int countTimes = 0;
    while(countTimes < 5 && next_permutation(value,value + w)){
        for(int i = 0;i < w;i++) cout << (char)(value[i] + 'a');
        cout << endl;
    }
    return 0;
}
