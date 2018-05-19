#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,s;
    cin >> n >> s;
    int *values = new int[n + 1];
    values[0] = 0;
    int h1,m1;
    cin >> h1 >> m1;
    values[1] = h1 * 60 + m1;
    if(values[1] >= s + 1) {
        cout << "0 0" << endl;
        return 0;
    }
    for(int i = 2;i <= n;i++) {
        int h,m;
        cin >> h >> m;
        int value = h * 60 + m;
        values[i] = value;
        if(values[i] - values[i - 1] > 2 * s + 1) {
            int downValue = values[i - 1] + s + 1;
            int nowH = downValue / 60;
            cout << nowH << " " << downValue % 60 << endl;
            return 0;
        }
    }
    int downValue = values[n] + s + 1;
    cout << downValue / 60 << " " << downValue % 60 << endl;
    return 0;
}
