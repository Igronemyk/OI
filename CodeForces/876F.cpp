#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

set<int> value[21];

int main() {
    int n;
    cin >> n;
    int result = 0;
    for(int i = 1;i <= n;i++) {
        int tmpValue,tmpResult = 0;
        cin >> tmpValue;
        set<int> nowResult;
        for(int j = 0;j < 21;j++) {
            if(!(tmpValue & (1 << j))) {
                value[j].insert(i);
            }else {
                nowResult.insert(value[j].begin(),value[j].end());
            }
        }
        result += static_cast<int>(nowResult.size());
    }
    cout << result << endl;
    return 0;
}
