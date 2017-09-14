#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    string s1,s2;
    cin >> s1 >> s2;
    if(s1.size() < s2.size() || (s1.size() == s2.size() && s1 < s2)){
        string tmp = s1;
        s1 = s2;
        s2 = tmp;
        cout << '-';
    }
    int maxSize = static_cast<int>(s1.size()),size2 = static_cast<int>(s2.size());
    int *value = new int[maxSize];
    fill(value,value + maxSize,0);
    for(int i = maxSize - 1;i >= 0;i--) value[maxSize - 1 - i] = s1[i] - '0';
    for(int i = size2 - 1;i >= 0;i--) value[size2 - 1 - i] -= s2[i] - '0';
    for(int i = 0;i < maxSize - 1;i++){
        while(value[i] < 0){
            value[i] += 10;
            value[i + 1]--;
        }
    }
    bool isStart = false;
    for(int i = maxSize - 1;i >= 0;i--){
        if(!isStart && value[i] == 0) continue;
        if(!isStart) isStart = true;
        cout << value[i];
    }
    if(!isStart) cout << 0;
    return 0;
}
