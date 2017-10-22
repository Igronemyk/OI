#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    set<string> result;
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) {
        string s;
        cin >> s;
        int pos = - 1;
        while((pos = s.find("u")) != -1) {
            s.replace(pos,1,"oo");
        }
        while((pos = s.find("kh")) != -1) {
            s.replace(pos,2,"h");
        }
        result.insert(s);
    }
    cout << result.size() << endl;
    return 0;
}
