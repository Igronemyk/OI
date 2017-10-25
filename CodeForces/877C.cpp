#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int len = (n / 2) * 2 + (n - n / 2);
    cout << len << endl;
    for(int i = 2;i <= n;i += 2) {
        cout << i << " ";
    }
    for(int i = 1;i <= n;i += 2) {
        cout << i << " ";
    }
    for(int i = 2;i <= n;i += 2) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
