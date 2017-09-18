#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

char result[300001];

int main(){
    string s1,s2;
    cin >> s1 >> s2;
    sort(s1.begin(),s1.end());
    sort(s2.begin(),s2.end(),greater<char>());
    int n = static_cast<int>(s1.size());
    int startS1 = 0,endS1 = (n + 1) / 2 - 1,startS2 = 0,endS2 = n / 2 - 1,startResult = 0,endResult = n - 1;
    for(int i = 0;i < n;i++){
        if(i & 1){
            if(s2[startS2] <= s1[startS1]){
                result[endResult--] = s2[endS2--];
            }else{
                result[startResult++] = s2[startS2++];
            }
        }else{
            if(s1[startS1] >= s2[startS2]){
                result[endResult--] = s1[endS1--];
            }else{
                result[startResult++] = s1[startS1++];
            }
        }
    }
    for(int i = 0;i < n;i++){
        cout << result[i];
    }
    cout << endl;
    return 0;
}
