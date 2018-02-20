#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    double oneCost = INF;
    for(int i = 0;i < n;i++) {
        int a,b;
        cin >> a >> b;
        oneCost = min(oneCost,a * 1.00 / (b * 1.00));
    }
    printf("%.8lf\n",oneCost * m);
    return 0;
}
