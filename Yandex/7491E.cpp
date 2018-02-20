#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 1e5;

int nxtPos[MAXN + 1],values[MAXN + 1],firstPos[MAXN + 1];
bool isQuery[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,k;
    cin >> n >> k;
    map<string,int> id;
    map<int,int> pre;
    int nowId = 1;
    for(int i = 1;i <= n;i++) {
        string tmp;
        cin >> tmp;
        int tmpId = id[tmp];
        if(tmpId == 0) {
            tmpId = nowId++;
            id[tmp] = tmpId;
            firstPos[tmpId] = i;
            pre[tmpId] = i;
        }else {
            nxtPos[pre[tmpId]] = i;
            pre[tmpId] = i;
        }
        values[i] = tmpId;
    }
    bool flag = true;
    int initPos = 1;
    for(int i = 1;i <= k;i++) {
        string tmp;
        cin >> tmp;
        int tmpId = id[tmp];
        if(tmpId == 0) {
            flag = false;
        }else {
            initPos = max(initPos,firstPos[tmpId]);
            isQuery[tmpId] = true;
        }
    }
    if(!flag) {
        cout << 0 << endl;
        return 0;
    }
    int endPos = initPos;
    long long result = n - endPos + 1;
    for(int i = 2;i <= n;i++) {
        if(isQuery[values[i - 1]]) {
            if(nxtPos[i - 1] == 0) {
                break;
            }
            endPos = max(endPos,nxtPos[i - 1]);
        }
        result += n - endPos + 1;
    }
    cout << result << endl;
    return 0;
}
