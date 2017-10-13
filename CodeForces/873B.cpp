#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pre;
    int length = n;
    pre.reserve(length + 1);
    pre.push_back(0);
    int result = 0;
    for(int i = 0;i < length;i++){
        int nowValue = s[i] - '0';
        pre.push_back(pre.back() + nowValue);
        int nowMaxRange = min(i + 1 - pre[i + 1],pre[i + 1]);
        for(int j = nowMaxRange;j > result;j--){
            int startPos = i + 1 - j * 2;
            if(pre[i + 1] - pre[startPos] == j){
                result = j;
                break;
            }
        }
    }
    cout << result * 2 << endl;
    return 0;
}
