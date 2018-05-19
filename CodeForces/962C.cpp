#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAXN = 11;
const int EPS = 1e-8;

int values[MAXN],nowResult[MAXN],nowResultCnt,nowCnt;

bool check(int nowSelect) {
    int value = 0;
    for(int i = nowSelect - 1;i >= 0;i--) {
        value = value * 10 + nowResult[i];
    }
    if(value == 0) return false;
    double sqrtValue = sqrt(value);
    if(sqrtValue - static_cast<int>(sqrtValue) <= EPS && static_cast<int>(sqrtValue) - sqrtValue <= EPS) {
        return true;
    }else {
        return false;
    }
}

int getCnt(int nowSelect) {
    int result = nowSelect;
    for(int i = nowSelect - 1;i >= 0;i--) {
        if(nowResult[i] == 0) {
            result--;
        }else {
            break;
        }
    }
    return result;
}
void dfs(int now,int nowSelect) {
    if(now == nowCnt) {
        if(check(nowSelect)) {
            nowResultCnt = max(nowResultCnt,getCnt(nowSelect));
        }
        return;
    }
    nowResult[nowSelect] = values[now];
    dfs(now + 1,nowSelect + 1);
    dfs(now + 1,nowSelect);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    while(n) {
        values[nowCnt++] = n % 10;
        n /= 10;
    }
    dfs(0,0);
    if(nowResultCnt == 0) {
        cout << -1 << endl;
    }else {
        cout << nowCnt - nowResultCnt << endl;
    }
    return 0;
}

