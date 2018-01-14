#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    multiset<int> values,canPutIn;
    for(int i = 0;i < n;i++) {
        int tmpValue;
        cin >> tmpValue;
        values.insert(tmpValue);
        canPutIn.insert(tmpValue);
    }
    while(true) {
        int tmpValue = *(values.begin());
        multiset<int>::iterator it = canPutIn.upper_bound(tmpValue);
        if(it == canPutIn.end()) {
            break;
        }
        values.erase(values.begin());
        canPutIn.erase(it);
    }
    cout << values.size() << endl;
    return 0;
}
