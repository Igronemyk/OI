#include <iostream>

using namespace std;

const int MAXN = 300010;

bool visit[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << 1 << " ";
    int n;
    cin >> n;
    int cutLength = 0;
    for(int i = 1;i <= n;i++) {
        int cutValue;
        cin >> cutValue;
        visit[cutValue] = true;
        if(cutValue == n - cutLength) {
            while(cutLength < n && visit[n - cutLength]) {
                cutLength++;
            }
        }
        cout << i - cutLength + 1 << " ";
    }
    cout << endl;
    return 0;
}
