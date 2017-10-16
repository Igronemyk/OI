#include <iostream>
#include <iostream>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

bool visitA[10],visitB[10];

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        visitA[tmpValue] = true;
    }
    for(int i = 0;i < m;i++) {
        int tmpValue;
        cin >> tmpValue;
        visitB[tmpValue] = true;
    }
    for(int i = 1;i < 10;i++) {
        if(visitA[i] && visitB[i]) {
            cout << i << endl;
            return 0;
        }
    }
    int nowValue = 11;
    while(nowValue < 100) {
        int first = nowValue % 10;
        int second = nowValue / 10;
        if(visitA[first] && visitB[second]) {
            break;
        }
        if(visitA[second] && visitB[first]) {
            break;
        }
        nowValue++;
    }
    cout << nowValue << endl;
    return 0;
}
