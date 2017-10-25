#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string strs[] = {"Danil","Olya","Slava","Ann","Nikita"};
    string s;
    cin >> s;
    int status = 0;
    for(int i = 0;i < 5;i++) {
        int pos = -1;
        while((pos = s.find(strs[i],pos + 1)) != -1) {
            status++;
        }
    }
    cout << (status == 1 ? "YES" : "NO") << endl;
    return 0;
}
