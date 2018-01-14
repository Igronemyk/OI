#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    int *values = new int[n];
    int result = INF;
    for(int i = 0;i < n;i++) {
        cin >> values[i];
        if(k % values[i] == 0) {
            result = min(result,k / values[i]);
        }
    }
    cout << result << endl;
    return 0;
}
