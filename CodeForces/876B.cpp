#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k,m;
    cin >> n >> k >> m;
    vector<vector<int> > value(m,vector<int>());
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        int afterMod = tmpValue % m;
        value[afterMod].push_back(tmpValue);
    }
    int result = -1;
    for(int i = 0;i < m;i++) {
        if(value[i].size() >= k) {
            result = i;
            break;
        }
    }
    if(result == -1) {
        cout << "No" << endl;
    }else {
        cout << "Yes" << endl;
        for(int i = 0;i < k;i++) {
            cout << value[result][i] << " ";
        }
        cout << endl;
    }
    return 0;
}
