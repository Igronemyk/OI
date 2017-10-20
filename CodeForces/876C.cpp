#include <iostream>
#include <vector>

using namespace std;

int getNum(int val) {
    int sum = 0;
    while(val) {
        sum += val % 10;
        val /= 10;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int checkValue = n - 100;
    vector<int> result;
    for(int i = checkValue;i <= n;i++) {
        if(i < 0) continue;
        int num = getNum(i);
        if(i + num == n) result.push_back(i);
    }
    cout << result.size() << endl;
    for(vector<int>::iterator it = result.begin();it != result.end();it++) {
        cout << *it << " ";
    }
    if(result.size() != 0) cout << endl;
    return 0;
}
