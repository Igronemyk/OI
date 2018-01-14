#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int A,B;
    cin >> A >> B;
    int x,y,z;
    cin >> x >> y >> z;
    long long countA = 0,countB = 0;
    countA += x * 2;
    countA += y;
    countB += y;
    countB += z * 1LL * 3;
    long long needA = (A > countA ? 0 : countA - A),needB = (B > countB ? 0 : countB - B);
    cout << needA + needB << endl;
    return 0;
}
