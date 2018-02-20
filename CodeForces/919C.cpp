#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    string *values = new string[n];
    int result = 0;
    for(int i = 0;i < n;i++) {
        string str;
        cin >> str;
        values[i] = str;
        int nowCnt = 0;
        for(string::iterator it = str.begin();it != str.end();it++) {
            if(*it == '.') {
                nowCnt++;
            }else {
                if(nowCnt >= k) {
                    result += nowCnt - k + 1;
                }
                nowCnt = 0;
            }
        }
        if(nowCnt >= k) {
            result += nowCnt - k + 1;
        }
    }
    if(k != 1) {
        for(int i = 0;i < m;i++) {
            int nowCnt = 0;
            for(int j = 0;j < n;j++) {
                if(values[j][i] == '.') {
                    nowCnt++;
                }else {
                    if(nowCnt >= k) {
                        result += nowCnt - k + 1;
                    }
                    nowCnt = 0;
                }
            }
            if(nowCnt >= k) {
                result += nowCnt - k + 1;
            }
        }
    }
    printf("%d\n",result);
    return 0;
}
