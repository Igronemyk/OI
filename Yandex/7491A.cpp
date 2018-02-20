#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAX_VAL_RANGE = 32;

bool visit[MAX_VAL_RANGE + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(visit,false,sizeof(visit));
    for(int i = 0;i < 10;i++) {
        int tmpValue;
        cin >> tmpValue;
        visit[tmpValue] = true;
    }
    int n;
    cin >> n;
    while(n--) {
        int countSelected = 0;
        for(int i = 0;i < 6;i++) {
            int tmpValue;
            cin >> tmpValue;
            if(visit[tmpValue]) {
                countSelected++;
            }
        }
        if(countSelected >= 3) {
            cout << "Lucky" << endl;
        }else {
            cout << "Unlucky" << endl;
        }
    }
    return 0;
}
