#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>

using namespace std;

const long long INF = 1.2e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long a,b,p,x;
    cin >> a >> b >> p >> x;
    long long nowValue = b;
    while(nowValue < INF) {

        nowValue += p;
    }
    return 0;
}
