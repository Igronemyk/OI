#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstddef>
#include <map>
#include <vector>

using namespace std;

long long getA(long long x,long long y,long long a,long long b) {
    return x * a + y * b;
}

long long getB(long long x,long long y,long long a,long long b) {
    return x * b - y * a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    long long a,b;
    cin >> n >> a >> b;
    map<long long,vector<long long> > values;
    for(int i = 0;i < n;i++) {
        long long e,x,y;
        cin >> e >> x >> y;
        long long valueX = getA(x,y,1,a),valueY = getB(x,y,1,a);
        values[valueY].push_back(valueX);
    }
    long long result = 0;
    for(map<long long,vector<long long> >::iterator it = values.begin();it != values.end();it++) {
        vector<long long> &tmpVec = it->second;
        sort(tmpVec.begin(),tmpVec.end());
        long long nowValue = 0,nowCnt = 0;
        bool start = false;
        int length = static_cast<int>(tmpVec.size());
        for(vector<long long>::iterator it1 = tmpVec.begin();it1 != tmpVec.end();it1++) {
            if(!start) {
                nowValue = *it1;
                nowCnt = 1;
                start = true;
            }else {
                if(*it1 == nowValue) {
                    nowCnt++;
                }else {
                    result += nowCnt * (length - nowCnt);
                    nowValue = *it1;
                    nowCnt = 1;
                }
            }
        }
        result += nowCnt * (length - nowCnt);
    }
    cout << result << endl;
    return 0;
}
