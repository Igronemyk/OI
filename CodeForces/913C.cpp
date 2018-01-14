#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

const long long INF = 9223372036854775807ll;


int quickPow(int a,int b) {
    int result = 1,base = a;
    while(b) {
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,L;
    cin >> n >> L;
    long long *canValue = new long long[31];
    fill(canValue,canValue + 31,INF);
    for(int i = 0;i < n;i++) {
        cin >> canValue[i];
    }
    for(int i = 1;i < 31;i++) {
        canValue[i] = min(canValue[i - 1] * 2,canValue[i]);
    }
    bool *isBuy = new bool[31];
    memset(isBuy,false,sizeof(bool) * 31);
    int countSign = 0;
    while(L) {
        isBuy[countSign++] = L & 1;
        L >>= 1;
    }
    unsigned long long result = 0;
    for(int i = 0;i < 30;i++) {
        result = min(result + (isBuy[i] ? canValue[i] : 0),static_cast<unsigned long long>(canValue[i + 1]));
    }
    cout << result << endl;
    return 0;
}

