#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int lastTime = 0;
    for(int i = 0;i < n;i++) {
        int s,d;
        cin >> s >> d;
        if(lastTime < s) {
            lastTime = s;
        }else {
            int nowCheckTime = s;
            while(nowCheckTime <= lastTime) {
                nowCheckTime += d;
            }
            lastTime = nowCheckTime;
        }
    }
    cout << lastTime << endl;
    return 0;
}
