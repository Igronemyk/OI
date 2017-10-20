#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int zeroCount = 0,oneCount = 0,result = 0;
    map<int,int> mp;
    mp[0] = -1;
    for(int i = 0;i < n;i++) {
        if(s[i] == '0') {
            zeroCount++;
        }else if(s[i] == '1') {
            oneCount++;
        }
        if(mp.count(oneCount - zeroCount) != 0) {
            result = max(result,i - mp[oneCount - zeroCount]);
        }else {
            mp[oneCount - zeroCount] = i;
        }
    }
    cout << result << endl;
    return 0;
}
