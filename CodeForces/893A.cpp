#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    bool flag = true,*isPlay = new bool[3];
    fill(isPlay,isPlay + 3,false);
    isPlay[0] = true;
    isPlay[1] = true;
    while(N--) {
        int tmpValue;
        cin >> tmpValue;
        tmpValue--;
        if(!isPlay[tmpValue]) {
            flag = false;
            break;
        }else {
            for(int i = 0;i < 3;i++) {
                if(i == tmpValue) continue;
                isPlay[i] = !isPlay[i];
            }
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
    return 0;
}
